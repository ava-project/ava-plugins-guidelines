#include "ava_api.pb.h"

#include <assert.h>
#include <iostream>
#define NDEBUG


void basic() {
  api::Plugin plugin;

  assert(plugin.GetDescriptor());

  plugin.set_name("firefox");
  plugin.set_command("start firefox");

  std::cout << plugin.name() << std::endl;
  std::cout << plugin.command() << std::endl;

  assert(plugin.name() == "firefox");
  assert(plugin.command() == "start firefox");
}

void serialization() {
  std::string s1;
  std::string s2;
  api::Plugin plugin;
  api::Plugin result;

  plugin.set_name("google-chrome");
  plugin.set_name("start google-chrome");
  plugin.SerializeToString(&s1);
  std::cout << s1 << std::endl;
  result.ParseFromString(s1);
  result.SerializeToString(&s2);
  std::cout << s2 << std::endl;
  assert(s1 == s2);
}

int main() {

  basic();
  serialization();
  return 0;
}
