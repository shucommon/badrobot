import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

x_data = np.random.rand(100)
noise = np.random.normal(0,0.01,x_data.shape)
y_data = x_data * 0.1 + 0.2 + noise

plt.scatter(x_data, y_data)
plt.show()

d = tf.Variable(np.random.rand(1))
k = tf.Variable(np.random.rand(1))
y = k * x_data + d

# 二次代价函数
loss = tf.losses.mean_squared_error(y_data, y)
# 定义一个梯度下降法优化器
optimizer = tf.train.GradientDescentOptimizer(0.3)
# 最小化代价函数
train = optimizer.minimize(loss)

# init variable
init = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)
    for i in range(201):
        sess.run(train)
        if i % 20 == 0:
            print(i, sess.run([k,d]))
    y_predict = sess.run(y)
    plt.scatter(x_data, y_data)
    plt.plot(x_data, y_predict, 'r-', lw=3)
    plt.show()

