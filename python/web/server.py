from wsgiref.simple_server import make_server
from hello import application
import sys

port = 8080
if len(sys.argv) == 2:
    port = int(sys.argv[1])

# create a server, ip leave for blank, handle funciton is application
httpd = make_server('', port, application)
print "servering HTTP on port %s..." % str(port)

# listen HTTP request
httpd.serve_forever()
