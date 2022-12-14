import socket
import sys
import os

server_address = "/tmp/py_sock"

sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)


try:
    sock.connect(server_address)
except Exception as msg:
    print(msg)
    sys.exit(1)

try:
    message = "Hey this is the msg from client. It will be repeated"
    sock.sendall(bytes(message, "utf-8"))
    amount_received = 0
    amount_expected = len(message)
    while amount_received < amount_expected:
        data = sock.recv(16)
        amount_received += len(data)
        print("recieved : ", data)
finally:
    sock.close()
