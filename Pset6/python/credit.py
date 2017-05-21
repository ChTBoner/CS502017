#!/usr/bin/python3

def first_digit(card_num):
    while card_num > 100:
        card_num = int(card_num / 10)

    return card_num

def checksum(card_num):
    sum_1 = 0
    sum_2 = 0

    while card_num > 0:
        #step 1
        sum_1 += card_num % 10
        card_num = int(card_num / 10)
        
        # step 2
        to_multiply = (card_num % 10) * 2

        if to_multiply >= 10:
            to_multiply = (to_multiply % 10) + int(to_multiply / 10)
        
        sum_2 += to_multiply
        card_num = int(card_num / 10)

    if ((sum_1 + sum_2) % 10) == 0:
        return True
    else: return False

def print_card_type(first_digit):
    if first_digit in range (40,51):
        print("VISA")
    elif first_digit in range (51,56):
        print("MASTERCARD")
    elif first_digit in (34, 37):
        print("AMEX")
    else: print("INVALID")

if __name__ == '__main__':
    card_num  = input("Please provide your credit card number : ")

    if checksum(int(card_num)):
        print_card_type(first_digit(int(card_num)))
    else: print('INVALID')

'''
American Express 378282246310005

American Express 371449635398431

American Express Corporate 378734493671000

MasterCard 5555555555554444

MasterCard 5105105105105100

Visa 4111111111111111

Visa 4012888888881881
'''