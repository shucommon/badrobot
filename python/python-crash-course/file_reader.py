filename = 'pi_digits.txt'
with open(filename) as file_object:
    contents = file_object.read()   # read all
    #print(contents)
    print(contents.rstrip())

with open(filename) as file_object:
    for line in file_object:    # read line by line
        print(line.rstrip())

with open(filename) as file_object:
    lines = file_object.readlines()
print(lines)
for line in lines:
    print(line.rstrip())

filename = 'programming.txt'
with open(filename, 'w') as file_object:
    file_object.write("I love programming.")
