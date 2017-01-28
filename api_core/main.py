from PNL.tcp.server import server

if __name__ == "__main__":
    s = server("127.0.0.1", 27017)
    s.listen(50)
    print("server is running on ", s.host, ":", s.port)
    s.run()
