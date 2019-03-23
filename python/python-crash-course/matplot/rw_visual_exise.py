import matplotlib.pyplot as plt
from random_walk import RandomWalk

while True:
    rw = RandomWalk()
    rw.fill_walk()

    # figure size in inch, 80 pixels per inch
    #plt.figure(figsize=(10,6))

    plt.plot(rw.x_values, rw.y_values, linewidth=1)

    # hide axis
    plt.axes().get_xaxis().set_visible(False)
    plt.axes().get_yaxis().set_visible(False)

    plt.show()

    another_walk = input("Make another walk ? (y/n): ")
    if another_walk == 'n':
        break
