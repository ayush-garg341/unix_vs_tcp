import socket
import sys
import os

server_address = "/tmp/py_sock"

try:
    os.unlink(server_address)
except Exception as e:
    print("error: ", e)
    if os.path.exists(server_address):
        raise

# Create a unix socket
sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

# bind socket to address
sock.bind(server_address)

# Listen for incoming connection
sock.listen(1)

while True:
    connection, client_address = sock.accept()
    print("connection established by client :", client_address)

    try:
        # Receive the data in chunks and re-transmit it to the client
        while True:
            data = connection.recv(16)
            if data:
                print("recieved : ", data)
                print("Sending back to the client")
                connection.sendall(data)
            else:
                print("No more data from client")
                break
    finally:
        connection.close()
