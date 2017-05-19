#!/usr/bin/python3

def checksum(card_num):
    sum_1 = 0
    sum_2 = 0

    while card_num > 0:
        sum_1 = card_num % 10
        card_num = card_num / 10
        to_multiply = (card_num % 10) * 2

        if to_multiply <= 10:
            to_multiply = (to_multiply % 10) + (to_multiply / 10)
        
        sum_2 += to_multiply
        card_num = card_num / 10

        if (sum_1 + sum_2) % 10 == 0:
            return True
        else: return False

if __name__ == '__main__':
    card_num  = input("Please provide your credit card number : ")

    if checksum(int(card_num)):
        print('OK')
    else: print('INVALID')
