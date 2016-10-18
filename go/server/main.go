package main

import ("log"
       "net"
       "golang.org/x/net/context"
       "google.golang.org/grpc"
       pb "ava_api_go/test"

)

const (
      port = ":50051"
)

type server struct{}

func (s *server) Send(ctx context.Context, in *pb.Request) (*pb.Reply, error) {
     return &pb.Reply{Message: "Request[" + in.Name + " - command: " + in.Command + "]"}, nil
}

func main() {

     lis, err := net.Listen("tcp", port)
     if err != nil {
     	log.Fatalf("Failed to listen: %v", err)
     }
     s := grpc.NewServer()
     pb.RegisterSendToDaemonServer(s, &server{})
     if err := s.Serve(lis); err != nil {
     	log.Fatalf("Failed to serve: %v", err)
     }

}