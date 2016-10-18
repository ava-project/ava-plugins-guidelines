package main

import (
	"log"
	"os"
	"golang.org/x/net/context"
	"google.golang.org/grpc"
	pb "ava_api_go/test"

)

const (
	address		= "localhost:50051"
	defaultName	= "Firefox"

)

func main() {

     conn,err := grpc.Dial(address, grpc.WithInsecure())
     if err != nil {
     	log.Fatalf("did not connect: %v", err)
     }
     defer conn.Close()
     c := pb.NewSendToDaemonClient(conn)

     name := defaultName
     if len(os.Args) > 1 {
     	name = os.Args[1]
     }
     r, err := c.Send(context.Background(), &pb.Request{Name: name, Command: "start"})
     if err != nil {
     	log.Fatalf("cound not send: %v", err)
     }
     log.Printf("Response: %s", r.Message)
}
