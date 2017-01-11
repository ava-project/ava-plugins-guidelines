#include "Hermes.hpp"

using namespace hermes::network::tcp;

std::condition_variable condvar;

void sig_handler(int) { condvar.notify_all(); }

int main(void) {
  server server;

  server.on_connection([](const std::shared_ptr<client> &client) {

    client->async_receive(1024, [&](bool success, std::vector<char> buffer) {
      if (success) {
        int res = std::system(std::string(buffer.data()).c_str());

        client->async_send(
            not res ? "Command correctly executed\n"
                    : "Failed executing given command\n",
            [&](bool success, std::size_t bytes) { client->disconnect(); });

      } else
        client->disconnect();

    });

  });

  server.run("127.0.0.1", 27017);

  signal(SIGINT, &sig_handler);

  std::mutex mutex;
  std::unique_lock<std::mutex> lock(mutex);
  condvar.wait(lock);

  return 0;
}
