#!/usr/bin/python3

number = -1

while (number < 0 or number > 23):
    number = int(input("pick a number between 1 and 23 : "))
    
# rows
for i in range (0, number):
    spaces = ""
    hashes = "#"
    # print spaces
    for j in range(0, number -i):
        spaces += " "
    
    # print spaces
    for h in range(0, i):
        hashes += "#"
    
    print(spaces + hashes + "  " + hashes)
