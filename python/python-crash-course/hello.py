print("hello world")
msg1='I told my friend, "Python is my favorite language!"'
msg2="The language 'Python' is named after Monty Python, not the snake."
msg3="One of Python's strengths is its diverse and supportive community."
print(msg1)
print(msg2)
print(msg3)

name='hello world'
print(name.title())
print(name.upper())
print(name.lower())

name=" hello "
name.rstrip()   # end
name.lstrip()   # start
name.strip()    # both

bicycles = ['trek', 'cannondale', 'redline', 'specialized']
print(bicycles)
bicycles.append("new_one")
print(bicycles)
bicycles.insert(1, "insert-in-1")
print(bicycles)
del bicycles[0]
print(bicycles)
poped=bicycles.pop()
print(bicycles)
print(poped)
poped=bicycles.pop(1)
print(bicycles)
print(poped)
bicycles.remove("redline")
print(bicycles)

cars = ['bmw', 'audi', 'toyota', 'subaru']
print(cars)
cars.sort()
print(cars)
cars.sort(reverse=True)
print(cars)
print("reverse interate")
cars.reverse()
print(cars)

cars = ['bmw', 'audi', 'toyota', 'subaru']
print("Here is the original list:")
print(cars)
print("Here is the sorted list:")
print(sorted(cars))
print("Here is the original list again:")
print(cars)
print(sorted(cars, reverse=True))
print("Here is the original list again:")
print(cars)
print("len of list cars:")
print(len(cars))

magicians = ['alice', 'david', 'carolina']
for magician in magicians:
    print(magician)

numbers = list(range(1,6))
print(numbers)

even_numbers = list(range(2,11,2))
print(even_numbers)

digits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]
print("min ", min(digits))
print("max ", max(digits))
print("sum ", sum(digits))

squares = [value**2 for value in range(1,11)]
print(squares)

alien = {'color' : 'green', 'points' : '5'}
print(alien['color'])
print(alien['points'])
alien = {1 : 'green', 2 : 5}
print(alien[1])
print(alien[2])

alien_0 = {'color': 'green', 'points': 5}
alien_1 = {'color': 'yellow', 'points': 10}
alien_2 = {'color': 'red', 'points': 15}
aliens = [alien_0, alien_1, alien_2]
for alien in aliens:
    print(alien)
'''
message = input("Tell me something, and I will repeat it back to you: ")
print(message)

age = input("how old are you ?")
age = int(age)
print(age)

current_number = 1
while current_number <= 5:
    print(current_number)
    current_number += 1
'''

pets = ['dog', 'cat', 'dog', 'goldfish', 'cat', 'rabbit', 'cat']
print(pets)
while 'cat' in pets:
    print("find")
    pets.remove('cat')
print(pets)

def func(*parm):
    #print(parm)
    for p in parm:
        print(p)

func('a')
func('a', 'b')

def build_profile(first, last, **user_info):
    profile = {}
    profile['first_name'] = first
    profile['last_name'] = last

    for key, value in user_info.items():
        profile[key] = value

    return profile

user_profile = build_profile('albert', 'einstein',
                            location='princeton',
                            field='physics')
print(user_profile)

class Dog():
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def sit(self):
        print(self.name.title() + " is now sitting.")
    def roll_over(self):
        print(self.name.title() + " rolled over!")

my_dog = Dog('willie', 6)
my_dog.sit()
my_dog.roll_over()

class Battery():
    def __init__(self, battery_size=70):
        self.battery_size = battery_size

    def describe_battery(self):
        print("This car has a " + str(self.battery_size) + "-kWh battery.")

    def get_range(self):
        if self.battery_size == 70:
            range = 240
        elif self.battery_size == 85:
            range = 270
        message = "This car can go approximately " + str(range)
        message += " miles on a full charge."
        print(message)

class Car():
    def __init__(self, make, model, year):
        self.make = make
        self.model = model
        self.year = year
        self.odometer_reading = 0

    def get_descriptive_name(self):
        long_name = str(self.year) + ' ' + self.make + ' ' + self.model
        return long_name.title()

    def read_odometer(self):
        print("This car has " + str(self.odometer_reading) + " miles on it.")

    def update_odometer(self, mileage):
        if mileage >= self.odometer_reading:
            self.odometer_reading = mileage
        else:
            print("You can't roll back an odometer!")

    def increment_odometer(self, miles):
        self.odometer_reading += miles

class ElectricCar(Car):
    def __init__(self, make, model, year):
        super().__init__(make, model, year) # init father's property
        #self.battery_size = 70              # then add child class propraty
        self.battery = Battery()

    def describe_battery(self):
        print("This car has a " + str(self.battery_size) + "-kWh battery.")

my_tesla = ElectricCar('tesla', 'model s', 2016)
print(my_tesla.get_descriptive_name())
my_tesla.read_odometer()
#my_tesla.describe_battery()
my_tesla.battery.describe_battery()
my_tesla.battery.get_range()
