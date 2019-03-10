"""descriable"""

from car import ElectricCar

my_tesla = ElectricCar('tesla', 'model s', 2016)
print(my_tesla.get_descriptive_name())
my_tesla.read_odometer()
my_tesla.battery.describe_battery()
