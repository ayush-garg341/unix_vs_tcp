import socket

# Create a tcp/ip socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to address
server_address = ("localhost", 1234)
print("server listening on :", server_address)
sock.bind(server_address)

# listen on the above socket
sock.listen()

while True:
    # Wait for a connection
    connection, client_address = sock.accept()
    try:
        print("connected to client on client address : ", client_address)
        while True:
            data = connection.recv(16)
            if data:
                print("Received from client :", data)
                connection.sendall(data)
            else:
                print("No more data")
                break
    finally:
        # close the connection
        connection.close()
