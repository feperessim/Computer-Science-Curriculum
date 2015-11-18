#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int get_key(string key)
{
    return (isdigit(key[0]) != 0) ? atoi(key) : -1;
}

/* Encrypts a line using the caesar cipher by the formula Ci = (Pi + Ki) % 26 */
string encrypt(int key)
{
    int i;
    string plain_text = GetString();
    string result = malloc(strlen(plain_text) + 1);
    
    for (i = 0; plain_text[i] != '\0'; ++i) {
        if (plain_text[i] >= 'a' && plain_text[i] <= 'z') {
            result[i] = (plain_text[i] + key - 'a') % 26 + 'a';
        }     
        else if (plain_text[i] >= 'A' && plain_text[i] <= 'Z') {
            result[i] = (plain_text[i] + key - 'A') % 26 + 'A';
        }
        else {
            result[i] = plain_text[i];
        }
    }
    result[i] = '\0';
    return result;
}

int main(int argc, string argv[])
{
    if (argc == 1) {
        printf("Usage: './caesar key' Where key stands for a numeric value\n");
        return 1;
    }
    else if (argc == 2) {
        int key; 
        if ((key = get_key(argv[1])) < 0) {
            printf("Wrong argument\n");
            return 1;
        }
        string encrypted_text = encrypt(key);
        printf("%s\n", encrypted_text);
    }
    else {
        printf("Wrong number of arguments\n");
        return 1;
    }
    return 0;
}

