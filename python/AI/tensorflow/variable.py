import tensorflow as tf

x = tf.Variable([1,2])
y = tf.constant([2,3])
sub = tf.subtract(x,y)
add = tf.add(x, sub)

init = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)
    print(sess.run(sub))
    print(sess.run(add))
