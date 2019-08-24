import numpy as np
import matplotlib.pyplot as plt

# define input data, xor
X = np.array([[1,0,0],
              [1,0,1],
              [1,1,0],
              [1,1,1]])

# define label
Y = np.array([[0],
              [1],
              [1],
              [0]])

# 3-10-1  3 input, 1 hinden layer with 10 element, 1 output
# [-1,1]
V = np.random.random([3,10]) * 2 - 1
W = np.random.random([10,1]) * 2 - 1

# learning rate set
lr = 0.1

def sigmoid(x):
    return 1/(1 + np.exp(-x))

def dsigmoid(x):
    return x * (1 - x)

def update():
    global V, W

    # cal output of each layer
    L1 = sigmoid(np.dot(X,V))
    L2 = sigmoid(np.dot(L1,W))

    # cal learn signal of each layer
    L2_delta = (Y - L2) * dsigmoid(L2)
    L1_delta = L2_delta.dot(W.T) * dsigmoid(L1)

    # cal diff of each layer
    delta_W = lr * L1.T.dot(L2_delta)
    delta_V = lr * X.T.dot(L1_delta)

    # update w v
    W = W + delta_W
    V = V + delta_V

for i in range(10001):
    update()
    if i % 500 == 0:
        # cal output of each layer
        L1 = sigmoid(np.dot(X,V))
        L2 = sigmoid(np.dot(L1,W))
        loss = np.mean(np.square(Y - L2)/2)
        print('loss:', loss)

L2 = sigmoid(np.dot(L1,W))
print(L2)

def judge(x):
    if x >= 0.5:
        return 1
    else:
        return 0

for i in map(judge, L2):
    print(i)
