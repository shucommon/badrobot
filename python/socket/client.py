import socket

HOST = '192.168.1.120'  # The server's hostname or IP address
PORT = 8899 # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    data = s.recv(1024)

print('Received', repr(data))
