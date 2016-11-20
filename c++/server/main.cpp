#include "Netlib.hpp"

using namespace netlib;

int main() {
  network::tcp::server server;

  auto callback = [](const std::string& cmd, network::tcp::socket& client) {
    int res = std::system(std::string(cmd).c_str());

    client.send(not res ? "Command correctly executed.\n"
                        : "Failed executing given command.\n");

    client.close();
  };

  server.on_accept(callback);
  server.run("127.0.0.1", 8888);
  server.stop();
}
