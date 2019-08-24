import urllib.request

def download(path):
    print('Beginning file download with urllib2...')
    url = []
    url.append('http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz')
    url.append('http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz')
    url.append('http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz')
    url.append('http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz')

    name = []
    name.append('train-images-idx3-ubyte.gz')
    name.append('train-labels-idx1-ubyte.gz')
    name.append('t10k-images-idx3-ubyte.gz')
    name.append('t10k-labels-idx1-ubyte.gz')

    for i in range(4):
        print("downloading " + name[i])
        urllib.request.urlretrieve(url[i], path + '/' + name[i])
