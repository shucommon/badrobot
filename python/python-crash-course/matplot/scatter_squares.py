import matplotlib.pyplot as plt

x_values = list(range(1,1001))
y_values = [x**2 for x in x_values]
#plt.scatter(x_values, y_values, s=40)
#plt.scatter(x_values, y_values, c='red', edgecolor='none', s=40)
#plt.scatter(x_values, y_values, c=(0,0,0.8), edgecolor='none', s=40)
plt.scatter(x_values, y_values, c=y_values, cmap=plt.cm.Blues, edgecolor='none', s=40)

plt.title("square numbers", fontsize=24)
plt.xlabel("Value", fontsize=14)
plt.ylabel("square of value", fontsize=14)
plt.tick_params(axis='both', which='major', labelsize=14)
plt.axis([0, 1100, 0, 1100000])
plt.show()
#plt.savefig('squares_plot.png', bbox_inches='tight')
