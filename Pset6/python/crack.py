#!/usr/bin/python3

from crypt import crypt
import sys
import string
import itertools

def find_passwd(crypted_passwd, salt):
    chars = string.ascii_lowercase + string.ascii_uppercase
    for i in range(1, 5):
        for to_crypt_tup in itertools.product(chars, repeat=i):
            passwd = ''.join(to_crypt_tup)
            print(crypt(passwd, salt=salt))
            if crypt(passwd, salt=salt) == crypted_passwd:
                return passwd

if __name__=="__main__":
    # check command line arguments
    if len(sys.argv) != 2:
        print("Usage: ./crack.py passwd")
    
    # find the salt in string
    salt = sys.argv[1][0:2]
    
    # parse string
    passwd = find_passwd(sys.argv[1], salt)
    
    print(passwd)
