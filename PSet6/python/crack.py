#!/usr/bin/python3

from crypt import crypt
import sys
import string
import itertools

def find_passwd(crypted_passwd, salt):
    # create set of all lowercase and uppercase ASCII characters
    chars = string.ascii_lowercase + string.ascii_uppercase

    # allowing for up to 4 characters
    for i in range(1, 5):
        # generating up to 4 characters strings
        for to_crypt_tup in itertools.product(chars, repeat=i):
            # product() return a tuple, so creating a string with join()
            passwd = ''.join(to_crypt_tup)

            # using crypt() on the passwd string to check if it matches. 
            if crypt(passwd, salt=salt) == crypted_passwd:
                return passwd

if __name__=="__main__":
    # check command line arguments
    if len(sys.argv) != 2:
        print("Usage: ./crack.py passwd")
    
    # find the salt in string
    salt = sys.argv[1][0:2]
    
    # generate passwords
    passwd = find_passwd(sys.argv[1], salt)
    
    print(passwd)
