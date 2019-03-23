from die import Die
import pygal

die = Die()

results = []
for roll_num in range(1000):
    result = die.roll()
    results.append(result)

frequencies = []
for value in range(1, die.num_sides + 1):
    frequency = results.count(value)
    frequencies.append(frequency)

hist = pygal.Bar()

hist.title = "Results of rolling one d6 1000 times."
#hist.x_labels = ['1', '2', '3', '4', '5', '6']
hist.x_labels =[str(i) for i in range(1, 7)]
hist.x_title = "Result"
hist.y_title = "Frequency of result"

hist.add('D6', frequencies)
hist.render_to_file('die_visual.svg')
