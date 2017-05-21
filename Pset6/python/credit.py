#!/usr/bin/python3

def first_digit(card_num):
    while card_num < 100:
        card_num = card_num / 10

    print("card_num = " + card_num)
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

    print(sum_1)
    print(sum_2)
    result = sum_1 + sum_2
    print(type(result))
    #print("result = " + str(result))
    if (result % 10) == 0:
            print("TRUE")
            return True
    else: 
            print("FALSE")
            return False

def print_card_type(first_digit):
    # if 40 >= first_digit > 50:
    if first_digit in range (40,51):
        print("VISA")
    elif first_digit in range (51,56):
        print("MASTERCARD")
    elif first_digit in (34, 37):
        print("VISA")
    else: print("INVALID")

if __name__ == '__main__':
    card_num  = input("Please provide your credit card number : ")

    if checksum(int(card_num)):
        print_card_type(first_digit(int(card_num)))
    else: print('INVALID')
