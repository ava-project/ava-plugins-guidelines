#include "Hermes.hpp"

using namespace hermes::network::tcp;

std::condition_variable condvar;

void sig_handler(int) { condvar.notify_all(); }

void send_callback(const std::shared_ptr<client> &client, bool success,
                   std::size_t bytes_sent) {
  if (success)
    std::cout << bytes_sent << std::endl;
  else
    client->disconnect();
}

void receive_callback(const std::shared_ptr<client> &client, bool success,
                      std::vector<char> buffer) {
  if (success) {
    std::string succeed("Command correctly executed\n");
    std::string failed("Failed executing given command\n");

    int res = std::system(std::string(buffer.data()).c_str());
    client->async_send(not res ? succeed : failed,
                       std::bind(&send_callback, client, std::placeholders::_1,
                                 std::placeholders::_2));
  } else {
    client->disconnect();
  }
}

int main(void) {
  server server;

  server.on_connection([](const std::shared_ptr<client> &client) {

    client->async_receive(
        1024, std::bind(&receive_callback, client, std::placeholders::_1,
                        std::placeholders::_2));

  });

  server.run("127.0.0.1", 27017);

  signal(SIGINT, &sig_handler);

  std::mutex mutex;
  std::unique_lock<std::mutex> lock(mutex);
  condvar.wait(lock);

  return 0;
}
