# A float range function, implementation of https://stackoverflow.com/a/47877721
def frange(start, stop, step=1.0):
    """ Implementation of Python's ``range()`` function which works with floats.

    Reference to this implementation: https://stackoverflow.com/a/36091634

    :param start: start value
    :type start: float
    :param stop: end value
    :type stop: float
    :param step: increment
    :type step: float
    :param decimals: rounding number
    :type decimals: int
    :return: float
    :rtype: generator
    """
    i = 0.0
    x = float(start)  # Prevent yielding integers.
    x0 = x
    epsilon = step / 2.0
    yield x  # always yield first value
    while x + epsilon < stop:
        i += 1.0
        x = x0 + i * step
        yield x
    if stop > x:
        yield stop  # for yielding last value of the knot vector if the step is a large value, like 0.1
for i in frange(0, 1, 0.10):
    print "degree: " + str(degree) + " control_points_size: " + str(control_points_size) + " spacing: " + str(i)
    print i
