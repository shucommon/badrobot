import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
import sys
sys.path.append('./MNIST_data')

import os.path
from download import download
have_data = os.path.exists('MNIST_data/train-images-idx3-ubyte.gz')
if not have_data:
    download('./MNIST_data')

# load data
mnist = input_data.read_data_sets("MNIST_data", one_hot=True)

# batch
batch_size = 64
n_batch = mnist.train.num_examples // batch_size

# in [60000, 28 * 28]  out [60000, 10]
x = tf.placeholder(tf.float32, [None,784])
y = tf.placeholder(tf.float32, [None,10])
keep_prob = tf.placeholder(tf.float32)

# 神经网络结构 784-1000-500-10
w1 = tf.Variable(tf.truncated_normal([784,1000], stddev=0.1))
b1 = tf.Variable(tf.zeros([1000]) + 0.1)
l1 = tf.nn.tanh(tf.matmul(x, w1) + b1)
l1_drop = tf.nn.dropout(l1, keep_prob)

w2 = tf.Variable(tf.truncated_normal([1000, 500], stddev=0.1))
b2 = tf.Variable(tf.zeros([500]) + 0.1)
l2 = tf.nn.tanh(tf.matmul(l1_drop, w2) + b2)
l2_drop = tf.nn.dropout(l2, keep_prob)

w3 = tf.Variable(tf.truncated_normal([500, 10], stddev=0.1))
b3 = tf.Variable(tf.zeros([10]) + 0.1)
prediction = tf.nn.softmax(tf.matmul(l2_drop, w3) + b3)

# 正则项
l2_loss = tf.nn.l2_loss(w1) + tf.nn.l2_loss(b1) + tf.nn.l2_loss(w2) + tf.nn.l2_loss(b2) + tf.nn.l2_loss(w3) + tf.nn.l2_loss(b3)

# 二次代价函数 - 回归问题
# loss = tf.losses.mean_squared_error(y, prediction)
# 交叉墒-分类问题
loss = tf.losses.softmax_cross_entropy(y, prediction) + 0.0005 * l2_loss

# 梯度下降法优化器
train = tf.train.GradientDescentOptimizer(0.5).minimize(loss)

# save result to a bool array
# 1000 0000 00 -> 0
# 0100 0000 00 -> 1
# ...
correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(prediction, 1))
# correct rate, bool -> float ->mean
accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

with tf.Session() as sess:
    # init variable
    sess.run(tf.global_variables_initializer())

    for epoch in range(10):
        for batch in range(n_batch):
            # get a batch data and label
            batch_x, batch_y = mnist.train.next_batch(batch_size)
            sess.run(train, feed_dict={x:batch_x, y:batch_y, keep_prob:1})

        acc = sess.run(accuracy, feed_dict={x:mnist.test.images, y:mnist.test.labels, keep_prob:1.0})
        train_acc = sess.run(accuracy, feed_dict={x:mnist.train.images, y:mnist.train.labels, keep_prob:1.0})
        print("Iter " + str(epoch + 1) + ", Testing Accuracy " + str(acc) + ", Training Accuracy " + str(train_acc))
