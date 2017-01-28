from PNL.tcp.client import client

if __name__ == "__main__":
    c = client("127.0.0.1", 27017)
    print("client is connecting to ", c.host, ":", c.port)
