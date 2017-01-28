#pragma once

#include "Hermes/include/Hermes.hpp"

using namespace hermes::tools;
using namespace hermes::network;

namespace ava {

//
static std::string const HOST = "127.0.0.1";

//
static unsigned int const PORT = 27017;

//
tcp::client client;

//
void init(void) {
  std::cout << logger::info() + "Init TCP connection with the daemon\n";

  try {
    client.connect(HOST, PORT);
  } catch (const std::exception &e) {
    std::cerr << logger::error() + "Error connection to the daemon failed.\n";
    std::cerr << e.what();
  }
}

}  // namespace ava
