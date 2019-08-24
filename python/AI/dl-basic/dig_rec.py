import numpy as np
from sklearn.datasets import load_digits
from sklearn.preprocessing import LabelBinarizer
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, confusion_matrix
import matplotlib.pyplot as plt

# load data
digits = load_digits()

#debug
print(digits.images.shape)
plt.imshow(digits.images[0], cmap='gray')
plt.show()

# data
X = digits.data
# label
y = digits.target

# debug
print(X.shape)
print(y.shape)
print(X[:3])
print(y[:3])

# 64-100-10
V = np.random.random((64,100)) * 2 - 1
W = np.random.random((100,10)) * 2 - 1

# data split
# 1/4 test set  3/4 train set
X_train, X_test, y_train, y_test = train_test_split(X,y)

# label to bin
# 0 -> 1000000000
# 3 -> 0001000000
# 9 -> 0000000001
labels_train = LabelBinarizer().fit_transform(y_train)

# debug
print(y_train[:5])
print(labels_train[:5])

def sigmoid(x):
    return 1/(1 + np.exp(-x))

def dsigmoid(x):
    return x * (1 - x)

def train(X, y, steps=10000, lr=0.11):
    global V, W
    for n in range(steps + 1):
        # choice a random data
        i = np.random.randint(X.shape[0])
        x = X[i]
        x = np.atleast_2d(x)

        # BP
        # cal output of each layer
        L1 = sigmoid(np.dot(x,V))
        L2 = sigmoid(np.dot(L1,W))

        # cal learn signal of each layer
        L2_delta = (y[i] - L2) * dsigmoid(L2)
        L1_delta = L2_delta.dot(W.T) * dsigmoid(L1)

        # cal diff of each layer
        delta_W = lr * L1.T.dot(L2_delta)
        delta_V = lr * x.T.dot(L1_delta)

        # update w v
        W = W + delta_W
        V = V + delta_V

        if n % 1000 == 0:
            output = predict(X_test)
            predictions = np.argmax(output, axis=1)
            acc = np.mean(np.equal(predictions, y_test))
            print('steps:', n, 'accuracy:', acc)

def predict(x):
    # cal output of each layer
    L1 = sigmoid(np.dot(x,V))
    L2 = sigmoid(np.dot(L1,W))
    return L2

train(X_train, labels_train, 200000)
output = predict(X_test)
predictions = np.argmax(output, axis=1)
print(classification_report(predictions, y_test))
print(confusion_matrix(predictions, y_test))

