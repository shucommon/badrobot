import os

bsize = 16384
fin = os.open("foo", os.O_RDONLY)
fout = os.open("bar", os.O_WRONLY | os.O_CREAT, 0o644)

# this doesn't work because assignments don't return a value
#while(buf = os.read(fin, bsize)):
#    os.write(fout, buf)
while 1:
    buf = os.read(fin, bsize)
    if buf:
        os.write(fout, buf)
    else:
        break

os.close(fin)
os.close(fout)
