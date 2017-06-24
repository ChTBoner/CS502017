#!/usr/bin/env python3

import sys
import string

dictionaries_path = 'speller/dictionaries/'
texts_location = 'speller/texts/'

def remove_punctuation(word):
    word = word.strip(string.punctuation)
    return word

def set_dictionary(dictionary_path):
    dictionary_file = open(dictionary_path)
    dictionary = set()
    for line in dictionary_file:
        dictionary.add(line.rstrip())

    dictionary_file.close()
    
    return dictionary

def check_spelling(dictionary_path, text_path):
    # fill the dictionary with words
    dictionary = set_dictionary(dictionary_path)

    text = open(text_path)

    wrong_words = []
    for line in text:
        # split each line in words
        words = line.split()

        # remove punctuation and put to lowercase
        for word in words:
            to_check = remove_punctuation(word)
            if to_check.isalpha():
                # check if words in list are in dictionary
                if to_check.lower() not in dictionary:
                    wrong_words.append(to_check)

    text.close()
    return wrong_words

def print_results(wrong_words):
    for word in wrong_words:
        print(word)

    print("MISSPELLED = {}".format(len(wrong_words)))

def main(args):
    # set correct values to args
    if len(args) == 3 and args[1] == "dictionaries/small":
        dictionary_name = "small"
    else: dictionary_name = "large"

    if len(args) == 3:
        text_name = args[2]
    else : text_name = args[1]

    # set path to files
    dictionary_path = "{}{}".format(dictionaries_path, dictionary_name)
    text_path = "{}{}.txt".format(texts_location, text_name)

    #check spelling
    wrong_words = check_spelling(dictionary_path, text_path)

    print_results(wrong_words)

if __name__ == "__main__":
    if len(sys.argv) < 2 or len(sys.argv) > 3:
        print("Usage ./speller.py [dictionary] text")
    else:
        main(sys.argv)

