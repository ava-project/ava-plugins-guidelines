package ava_api

import(
  "net"
  "log"
  "fmt"
)

var conn net.Conn

const(
  address = "127.0.0.1:27017"
)

func init() {
  var err error

  fmt.Printf("INFO: Init connection to the daemon\n")

  conn, err = net.Dial("tcp", address)

  if err != nil {
    log.Fatalf("Connection to the daemon failed: %v", err)
  }


}

func close() {
  conn.Close()
}
