import zipfile
import optparse
from threading import Thread

def extractFile(zfile, passwd):
    try:
        zfile.extractall(pwd=passwd)
        print '[+] found password ' + passwd + '\n'
    except Exception, e:
        print '[-] bad password\n'
        pass

def main():
    parser = optparse.OptionParser("usage%prog " + "-f <zipfile> -d <dictionary>")
    parser.add_option('-f', dest = 'zname', type = 'string', help = 'specify zip file')
    parser.add_option('-d', dest = 'dname', type = 'string', help = 'specify dictionary file')
    (options, args) = parser.parse_args()
    if(options.zname == None) | (options.dname == None):
        print parser.usage
        exit(0)
    else:
        zname = options.zname
        dname = options.dname

    zfile = zipfile.ZipFile(zname)
    passfile = open(dname)
    for line in passfile.readlines():
        passwd = line.strip('\n')
        t = Thread(target = extractFile, args = (zfile, passwd))
        t.start()

if __name__ == '__main__':
    main()
