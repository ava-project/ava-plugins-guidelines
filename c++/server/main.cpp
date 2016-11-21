#include "Netlib.hpp"

using namespace netlib;

int main() {
  network::tcp::server server;

  auto callback = [](const std::string& cmd,
                     std::shared_ptr<network::tcp::client>& client) {
    int res = std::system(std::string(cmd).c_str());

    client->send(not res ? "Command correctly executed.\n"
                         : "Failed executing given command.\n");

    client->disconnect();
  };

  server.on_accept(callback);
  server.run("192.168.0.107", 8888);
  server.stop();
}
