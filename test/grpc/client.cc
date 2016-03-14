#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>

#include "ava_api.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using api::LecheMesCouilles;
using api::Plugin;
using api::Reply;

class Client {
public:
  Client(std::shared_ptr<Channel> channel)
       : stub_(LecheMesCouilles::NewStub(channel)) {}

   // Assambles the client's payload, sends it and presents the response back
   // from the server.
   std::string rapeagland(const std::string& name, const std::string& command) {
     // Data we are sending to the server.
     Plugin plugin;
     plugin.set_name(name);
     plugin.set_command(command);

     // Container for the data we expect from the server.
     Reply reply;

     // Context for the client. It could be used to convey extra information to
     // the server and/or tweak certain RPC behaviors.
     ClientContext context;

     // The actual RPC.
     Status status = stub_->rapeagland(&context, plugin, &reply);

     // Act upon its status.
     if (status.ok()) {
       return reply.message();
     } else {
       return "RPC failed";
     }
   }

  private:
   std::unique_ptr<LecheMesCouilles::Stub> stub_;
};


int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  Client client(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  std::string plugin("firefox");
  std::string command("start firefox");

  std::string reply = client.rapeagland(plugin, command);
  std::cout << "Client received: " << reply << std::endl;
  return 0;
}
