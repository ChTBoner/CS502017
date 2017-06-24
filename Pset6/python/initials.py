#!/usr/bin/env python3

name = input()
initials = ""

for i in name.split():
    initials += i[0]

print(initials)