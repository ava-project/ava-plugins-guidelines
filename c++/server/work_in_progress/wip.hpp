#pragma once

#include <stdio.h>
#include <atomic>
#include <chrono>
#include <ctime>
#include <functional>
#include <iomanip>
#include <map>
#include <memory>
#include <mutex>
#include <sstream>
#include <thread>
#include "Netlib.hpp"

namespace netlib {

namespace tools {

template <typename T>
std::size_t hash(const T &to_hash) {
  std::hash<T> h;
  return h(to_hash);
}

std::string get_current_time_and_date() {
  std::mutex mutex;
  std::stringstream ss;

  std::lock_guard<std::mutex> lock(mutex);
  {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
  }
  return ss.str();
}

}  //! namespace tools

namespace network {

using namespace tools;

namespace tcp {

//!
//! tcp client
//!
class client {
 public:
  //! ctor
  client(void) : is_connected_(false) {}

  //! creates a client from an existing socket
  explicit client(const socket &socket)
      : socket_(socket), is_connected_(true) {}

  //! copy ctor
  client(const client &) = delete;

  //! assignment operator
  client &operator=(const client &) = delete;

  //! dtor
  ~client(void) { disconnect(); }

 public:
  //! connects the client to the given endpoint
  void connect(const std::string &host, unsigned int port) {
    if (is_connected_)
      __LOGIC_ERROR__("tcp::client::connect: Client is already connected.");

    socket_.connect(host, port);
    is_connected_ = true;
  }

  //! sends amount of data
  std::size_t send(const std::string &message) {
    return send(std::vector<char>(message.begin(), message.end()),
                message.size());
  }

  //! sends amount of data
  std::size_t send(const std::vector<char> &data, std::size_t data_len) {
    if (not is_connected_)
      __LOGIC_ERROR__("tcp::client::send: Client must be connected.");

    return socket_.send(data, data_len);
  }

  //! receives amount of data
  std::vector<char> receive(std::size_t size_to_read) {
    if (not is_connected_)
      __LOGIC_ERROR__("tcp::client::receive: Client must be connected.");
    return socket_.receive(size_to_read);
  }

  //! disconnects the client
  void disconnect() {
    if (not is_connected_) return;

    socket_.close();
    is_connected_ = false;
  }

  //! returns true/false whether the client is already connected
  bool is_connected() const { return is_connected_; }

 private:
  //! client socket
  socket socket_;

  //! boolean to know if the client is already connected
  std::atomic_bool is_connected_;
};

//!
//! tcp server
//!

class server {
 public:
  //! ctor
  server(void) : is_running_(false), callback_(nullptr) {}

  //! copy ctor
  server(const server &) = delete;

  //! assignment operator
  server &operator=(const server &) = delete;

  //! dtor
  ~server(void) { stop(); }

 public:
  //! triggers a callback when a new client is accepted
  void on_accept(
      const std::function<void(const std::string &, std::shared_ptr<client> &)>
          &callback) {
    callback_ = callback;
  }

  //! starts the server
  void run(const std::string &host, unsigned int port) {
    if (is_running_)
      __RUNTIME_ERROR__("tcp::server::run: Server is aldready running.");

    socket_.bind(host, port);
    socket_.listen(tools::BACKLOG);
    is_running_ = true;
    process();
  }

  //! stops the server
  void stop(void) {
    if (not is_running_) return;

    socket_.close();
    for (auto &client : clients_) {
      client.second->disconnect();
    }
    clients_.clear();
    is_running_ = false;
  }

  //! returns true/false whether the server is running
  bool is_running() const { return is_running_; }

 private:
  //!
  void process() {
    try {
      auto to_hash = tools::get_current_time_and_date();
      auto id = tools::hash(to_hash);
      auto new_client = std::make_shared<client>(socket_.accept());

      clients_[id] = std::move(new_client);
      auto rcv = clients_[id]->receive(tools::BUFFER_SIZE);
      std::string cmd(rcv.data());
      std::string response("Executing command [");
      cmd.erase(cmd.end() - 1);
      response += cmd;
      response += "] ...\n";
      clients_[id]->send(response);
      if (callback_) callback_(cmd, clients_[id]);

    } catch (const std::exception &e) {
      __DISPLAY_ERROR__(e.what());
      stop();
    }
  }

 private:
  //! server socket
  socket socket_;

  //! boolean to know if the server is already running
  std::atomic_bool is_running_;

  // //! clients
  std::map<std::size_t, std::shared_ptr<client>> clients_;

  //! server behaviour
  std::function<void(const std::string &, std::shared_ptr<client> &)> callback_;
};

}  //! namespace tcp
}  //! namespace network
}  //! namespace netlib
