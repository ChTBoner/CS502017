#!/usr/bin/python3

owed = 0
while owed <= 0:
    owed = int(float(input("How much is owed ? ")) * 100)
print(owed)

quarters = 0
dimes = 0
nickels = 0
pennies = 0

if owed >= 25:
    quarters = int(owed / 25)
owed = owed - 25 * quarters

if owed >= 10:
    dimes = int(owed / 10)
owed = owed - 10 * dimes

if owed >= 5:
    nickels = int(owed / 5)
owed = owed - 5 * nickels

if owed > 0:
    pennies = owed

total = quarters + dimes + nickels + pennies
print(total)