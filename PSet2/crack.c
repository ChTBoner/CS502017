#define _XOPEN_SOURCE

#include "cs50.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SALTLENGTH 3
// #define DICT "/usr/share/dict/words"

// compile with : clang -o crack crack.c -lcrypt

// char* wordFileCheck(char* password, char* salt)

int main(int argc, string argv[])
{
    // verifier le bon appel avec les deux arguments
    if (argc != 2)
    {
        printf("Not enough args\n");
        return 1;
    }

    // char word[50];
    char* password = argv[1];
    char salt[SALTLENGTH];
    // bool found = false;
    char usrPasswd[5];
    // int attempts = 0;

    // trouver le salt du mot de passe
    strncpy(salt, password, 2);

    // importer le fichier words:
    // FILE* words = fopen(DICT, "r");

    // verifier si ouverture ok
    /*if (words == NULL)
    {
        printf("Could not open words file");
        return 2;
    }*/

    // parser les mots du fichier et les crypter pour comparer avec pass
    /* while (fgets(word, sizeof word, words))
    {
        // cripter le mot dans le dictionnaire et comparer
        if (strcmp(password, crypt(word, salt)) == 0)
        {
            fclose(words);
            printf("%s", word);
            return 0;
        }
    }

    // free memory by closing file
    fclose(words);
    */

    // generating strings and comparing
    printf("Generating strings\n");
    usrPasswd[4] = '\0';
    for(int i0 = 65; i0 < 127; i0++)
    {
        usrPasswd[0] = i0;
        for(int i1 = 65; i1 < 127; i1++)
        {
            usrPasswd[1] = i1;
            for (int i2 = 65; i2 < 127; i2++)
            {
                usrPasswd[2] = i2;
                for(int i3 = 65; i3 < 127; i3++)
                {
                    usrPasswd[3] = i3;
                    printf("%s\n", usrPasswd);

                }
            }
        }
    }
}
