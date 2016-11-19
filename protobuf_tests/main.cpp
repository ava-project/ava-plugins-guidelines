#include "ava_api.pb.h"

#include <assert.h>
#include <iostream>
#define NDEBUG

void verbose(int test, const std::string& message,
             const std::string& expected) {
  std::cout << "[TEST n° " + std::to_string(test) + "] : " + message
            << std::endl;
  std::cout << "*******************************************************\n";
  std::cout << "expected: " + expected << std::endl;
  std::cout << "*******************************************************\n";
}

void settings(const std::string& message) {
  std::cout << "/*\n";
  std::cout << "** " + message << std::endl;
  std::cout << "*/\n";
}

void basic() {
  api::Plugin plugin;

  verbose(1, "testing protobuf descriptor", "descriptor recoverable");
  assert(plugin.GetDescriptor());

  settings("setting a plugin with command.");
  plugin.set_name("firefox");
  plugin.set_command("start firefox");

  settings("plugin name and command should be correctly displayed.");
  std::cout << plugin.name() << std::endl;
  std::cout << plugin.command() << std::endl;

  verbose(2, "testing plugins", "intended attributes");
  assert(plugin.name() == "firefox");
  assert(plugin.command() == "start firefox");
}

void serialization() {
  std::string s1;
  std::string s2;
  api::Plugin plugin;
  api::Plugin result;

  settings("setting a plugin with command.");
  plugin.set_name("google-chrome");
  plugin.set_name("start google-chrome");
  settings("protobuf serialization to string.");
  plugin.SerializeToString(&s1);
  std::cout << s1 << std::endl;
  settings(
      "parsing the result to retrieve a protobuf and serialize it again to "
      "compare");
  result.ParseFromString(s1);
  result.SerializeToString(&s2);
  std::cout << s2 << std::endl;
  verbose(3, "protobuf serialization", "two strings should be the same");
  assert(s1 == s2);
}

void description() {
  api::Plugin plugin;
  const google::protobuf::Descriptor* descriptor = plugin.GetDescriptor();
  const google::protobuf::FieldDescriptor* name_field =
      descriptor->FindFieldByName("name");

  settings("setting plugin name");
  plugin.set_name("test");

  verbose(4, "testing protobuf fields",
          "type fo field name should be a string");
  assert(name_field != NULL);
  assert(name_field->type() == google::protobuf::FieldDescriptor::TYPE_STRING);
}

void reflection() {
  api::Plugin plugin;
  settings("setting protobuf reflection");
  const google::protobuf::Reflection* reflection = plugin.GetReflection();
  const google::protobuf::Descriptor* descriptor = plugin.GetDescriptor();
  const google::protobuf::FieldDescriptor* name_field =
      descriptor->FindFieldByName("name");

  plugin.set_name("emacs");
  verbose(5, "testing protobuf reflection",
          "retrieving plugin name using reflection should work");
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
