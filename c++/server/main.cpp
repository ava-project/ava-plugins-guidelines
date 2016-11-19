#include "Netlib.hpp"

using namespace netlib;

int main() {
  network::tcp::socket socket;

  // simple echo tcp server

  socket.bind("127.0.0.1", 8888);
  socket.listen(30);
  network::tcp::socket client = socket.accept();
  std::cout << "client FD: " + std::to_string(client.get_fd()) << std::endl;
  std::cout << "client HOST: " + client.get_host() << std::endl;
  std::cout << "client PORT: " + std::to_string(client.get_port()) <<
  std::endl;
  auto res = client.receive(1024);
  std::cout << res.data() << std::endl;
  client.send(res.data());
  socket.close();

  // simple tcp client

  // socket.connect("127.0.0.1", 8888);
  // socket.send("hello world\n");
  // auto res = socket.receive(1024);
  // std::cout << res.data() << std::endl;
  // socket.close();
}
