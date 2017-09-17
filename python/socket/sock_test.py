import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('127.0.0.1', 5000))
s.send('GET /signin HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: close\r\n\r\n')

buffer = []
while True:
    d = s.recv(1024)
    if d:
        buffer.append(d)
    else:
        break

data = ''.join(buffer)

header, html = data.split('\r\n\r\n', 1)
print 'header:\n' + header
print 'body:\n' + html

s.close()
