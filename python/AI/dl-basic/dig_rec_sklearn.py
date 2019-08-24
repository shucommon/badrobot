from sklearn.neural_network import MLPClassifier
from sklearn.datasets import load_digits
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report
import matplotlib.pyplot as plt

# load data
digits = load_digits()
x_data = digits.data
y_data = digits.target
print(x_data.shape)
print(y_data.shape)

# data split
# 1/4 test set  3/4 train set
x_train, x_test, y_train, y_test = train_test_split(x_data,y_data)

mlp = MLPClassifier(hidden_layer_sizes = (100, 50), max_iter=500)
mlp.fit(x_train, y_train)

predictions = mlp.predict(x_test)
print(classification_report(y_test, predictions))

