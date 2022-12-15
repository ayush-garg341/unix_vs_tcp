import socket

# create client socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the server
server_address = ("localhost", 1234)

try:
    sock.connect(server_address)
    # send data
    msg = "Hey this message is from client and its how you doing."
    sock.sendall(bytes(msg, "utf-8"))

    amount_received = 0
    amount_expected = len(msg)
    while amount_received < amount_expected:
        data = sock.recv(16)
        amount_received += len(data)
        if data:
            print("Received from server : ", data)
        else:
            print("No more data from server")
            break
finally:
    print("closing the socket")
    sock.close()
