import numpy as np
import matplotlib.pyplot as plt

# xor is nonlinear problem, can't use this method

# define input data, xor
X = np.array([[1,0,0],
              [1,0,1],
              [1,1,0],
              [1,1,1]])

# define label
T = np.array([[-1],
              [1],
              [1],
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
    Y = np.dot(X,W)
    # T-Y get del E(4,1)
    E = T - Y
    # cal w diff  X.T is the T of X. i.e mat(1,3) -> mat(3,1)
    delta_W = lr * (X.T.dot(E)) / X.shape[0]
    # update w
    W = W + delta_W

def draw():
    global W
    # positive sample x y cordornate
    x1 = [0, 1]
    y1 = [1, 0]
    # negitave sample x y cordornate
    x2 = [0, 1]
    y2 = [0, 1]
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
