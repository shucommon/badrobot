'''
y = sum(f(Xi * Wi)) i=(0,1,2...)
    y is the output of the net
    f is sign function(f = 1 with positive number, -1 with negative num
del(Wi) = n(t-y)Xi
    n is learning rate
    t is the expect output, label
    t and y can be 1 or -1
Wi = Wi + del(Wi)
'''
'''
asume we have 4 2d data : (3,3), (4,3), (1,1), (2,1),
corresponding label is 1 1 -1 -1
we make d also an input, so we get:
(1,3,3), (1,4,3), (1,1,1), (1,2,1),
label : (1,1,-1,-1)
w0,w1,w2 = (0,1)
lr(learning rate) = 0.1
active fun is sign func/Users/qiang/Desktop/dl-basic

w0 + w1x1 + w2x2 = 0 is the carve up line
make x1 = x, x2 = y, get a line
y = -w0/w2 -w1/w2 * x
'''

import numpy as np
import matplotlib.pyplot as plt

# define input data
X = np.array([[1,3,3],
              [1,4,3],
              [1,1,1],
              [1,2,1]])

# define label
T = np.array([[1],
              [1],
              [-1],
              [-1]])

# init w  3 row 1 col [0,1]
W = np.random.random([3,1])

# learning rate set
lr = 0.1

# neural net output
Y = 0

# update W fun
def train():
    global X, T, W, lr, Y
    # cal 4 data predict value, Y(4,1)
    Y = np.sign(np.dot(X,W))
    # T-Y get del E(4,1)
    E = T - Y
    # cal w diff  X.T is the T of X. i.e mat(1,3) -> mat(3,1)
    delta_W = lr * (X.T.dot(E)) / X.shape[0]
    # update w
    W = W + delta_W

def draw():
    # positive sample x y cordornate
    x1 = [3, 4]
    y1 = [3, 3]
    # negitave sample x y cordornate
    x2 = [1, 2]
    y2 = [1, 1]
    # define classify line
    k = -W[1]/W[2]
    d = -W[0]/W[2]
    # set two point to draw the line
    xdata = (0,5)
    plt.plot(xdata, xdata*k + d, 'r')
    # draw positive sample
    plt.scatter(x1, y1, c='g')
    # draw negitive sample
    plt.scatter(x2, y2, c='b')
    plt.show()

# train model
for i in range(100):
    # update w
    train()
    print('epoch:', i+1)
    print('weights:')
    print(W)
    print('***********************')

    Y = np.sign(np.dot(X,W))
    if (Y == T).all():
        print('Finished')
        break

draw()
