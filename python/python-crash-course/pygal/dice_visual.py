from die import Die
import pygal

die1 = Die()
die2 = Die()

results = []
for roll_num in range(1000):
    result1 = die1.roll()
    result2 = die2.roll()
    results.append(result1 + result2)

frequencies = []
for value in range(2, die1.num_sides + die2.num_sides + 1):
    frequency = results.count(value)
    frequencies.append(frequency)

'''
count = 0
for i in range(len(frequencies)):
    count += frequencies[i]
print(count)
'''

hist = pygal.Bar()

hist.title = "Results of rolling two d6 1000 times."
#hist.x_labels = ['1', '2', '3', '4', '5', '6']
hist.x_labels =[str(i) for i in range(2, 13)]
hist.x_title = "Result"
hist.y_title = "Frequency of result"

hist.add('2D6', frequencies)
hist.render_to_file('dice_visual.svg')
