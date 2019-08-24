import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

# get [200,1] data
x_data = np.linspace(-0.5, 0.5, 200)[:, np.newaxis]
noise = np.random.normal(0,0.02,x_data.shape)
y_data = np.square(x_data) + noise

plt.scatter(x_data, y_data)
plt.show()

x = tf.placeholder(tf.float32, [None,1])
y = tf.placeholder(tf.float32, [None,1])

# 神经网络结构 1-20-1
w1 = tf.Variable(tf.random_normal([1,20]))
b1 = tf.Variable(tf.zeros([20]))
l1_in = tf.matmul(x, w1) + b1
l1 = tf.nn.tanh(l1_in)

w2 = tf.Variable(tf.random_normal([20,1]))
b2 = tf.Variable(tf.zeros([1]))
l2_in = tf.matmul(l1, w2) + b2
prediction = tf.nn.tanh(l2_in)

# 二次代价函数
loss = tf.losses.mean_squared_error(y, prediction)
# 定义一个梯度下降法优化器
optimizer = tf.train.GradientDescentOptimizer(0.1)
# 最小化代价函数
train = optimizer.minimize(loss)

with tf.Session() as sess:
    # init variable
    sess.run(tf.global_variables_initializer())
    for _ in range(3000):
        sess.run(train, feed_dict={x:x_data, y:y_data})

    prediction_value = sess.run(prediction, feed_dict={x:x_data})
    plt.scatter(x_data, y_data)
    plt.plot(x_data, prediction_value, 'r-', lw=5)
    plt.show()

