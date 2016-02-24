#include "ava_api.pb.h"

#include <iostream>
#include <assert.h>
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

void description() {
  api::Plugin plugin;
  const google::protobuf::Descriptor* descriptor = plugin.GetDescriptor();
  const google::protobuf::FieldDescriptor* name_field = descriptor->FindFieldByName("name");

  plugin.set_name("test");

  assert(name_field != NULL);
  assert(name_field->type() == google::protobuf::FieldDescriptor::TYPE_STRING);
}

void reflection() {
  api::Plugin plugin;
  const google::protobuf::Reflection* reflection = plugin.GetReflection();
  const google::protobuf::Descriptor* descriptor = plugin.GetDescriptor();
  const google::protobuf::FieldDescriptor* name_field = descriptor->FindFieldByName("name");

  plugin.set_name("emacs");
  assert(reflection->GetString(plugin, name_field) == "emacs");
}

int main() {

  // Following functions provide a quick approach of Google Protocol buffers.
  // The purpose here is to ensure that the basics features are mastered.
  basic();
  serialization();
  description();
  reflection();
  return 0;
}
