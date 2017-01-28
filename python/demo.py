from PNL.tcp.server import server

if __name__ == "__main__":
    s = server("127.0.0.1", 27017)
    print("server running on ", s.host, ":", s.port)
