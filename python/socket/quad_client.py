import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('192.168.1.120', 8899))

while True:
    print s.recv(1024)

s.close()
