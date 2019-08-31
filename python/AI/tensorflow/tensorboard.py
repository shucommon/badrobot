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

with tf.name_scope('input'):
    # in [60000, 28 * 28]  out [60000, 10]
    x = tf.placeholder(tf.float32, [None,784], name='x-input')
    y = tf.placeholder(tf.float32, [None,10], name='y-input')

with tf.name_scope('layer'):
    # 神经网络结构 784-10
    with tf.name_scope('weights'):
        w = tf.Variable(tf.truncated_normal([784,10], stddev=0.1))
    with tf.name_scope('biases'):
        b = tf.Variable(tf.zeros([10]) + 0.1)
    with tf.name_scope('wx_plus_b'):
        wx_plus_b = tf.matmul(x, w) + b
    with tf.name_scope('softmax'):
        prediction = tf.nn.softmax(wx_plus_b)

with tf.name_scope('loss'):
    # 二次代价函数 - 回归问题
    loss = tf.losses.mean_squared_error(y, prediction)
    # 交叉墒-分类问题
    # loss = tf.losses.softmax_cross_entropy(y, prediction)

with tf.name_scope('train'):
    # 梯度下降法优化器
    train = tf.train.GradientDescentOptimizer(0.3).minimize(loss)

with tf.name_scope('accuracy'):
    # save result to a bool array
    # 1000 0000 00 -> 0
    # 0100 0000 00 -> 1
    # ...
    with tf.name_scope('correct_prediction'):
        correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(prediction, 1))
    with tf.name_scope('accuracy'):
        # correct rate, bool -> float ->mean
        accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

with tf.Session() as sess:
    # init variable
    sess.run(tf.global_variables_initializer())
    writer = tf.summary.FileWriter('logs/', sess.graph)

    '''
    for epoch in range(21):
        for batch in range(n_batch):
            # get a batch data and label
            batch_x, batch_y = mnist.train.next_batch(batch_size)
            sess.run(train, feed_dict={x:batch_x, y:batch_y})
        acc = sess.run(accuracy, feed_dict={x:mnist.test.images, y:mnist.test.labels})
        print("Iter " + str(epoch + 1) + ", Testing Accuracy " + str(acc))
    '''
