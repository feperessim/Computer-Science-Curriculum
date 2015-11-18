#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int check_wordkey(string wordkey)
{
    int i;

    for (i = 0; wordkey[i] != '\0'; ++i) {
        if (!((wordkey[i] >= 'a' && wordkey[i] <= 'z') || (wordkey[i] >= 'A' && wordkey[i] <= 'Z'))) {
            return -1;
        }
    }
    return 0;
}

string encrypt(string keyword)
{
    int i, k;
    int keyword_size = strlen(keyword);
    string plain_text = GetString();
    string result = malloc(strlen(plain_text) + 1);
    

    for (i = 0, k = 0; plain_text[i] != '\0'; ++i) {
        if (k >= keyword_size) {
            k = 0;
        }
        if (plain_text[i] >= 'a' && plain_text[i] <= 'z') {
            result[i] = (plain_text[i] -'a' + tolower(keyword[k]) - 'a') % 26 + 'a';
            ++k;
        }    
        else if (plain_text[i] >= 'A' && plain_text[i] <= 'Z') {
            result[i] = (plain_text[i] - 'A' + toupper(keyword[k]) - 'A') % 26 + 'A';
            ++k;
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
        printf("Usage: './vigenere' keyword\n");
        return 1;
    }
    else if (argc == 2) {
        if (check_wordkey(argv[1]) < 0) {
            printf("Wrong argument\n");
            return 1;
        }
        string encrypted_text = encrypt(argv[1]);
        printf("%s\n", encrypted_text);
    }
    else {
        printf("Wrong number of arguments\n");
        return 1;
    }
    return 0;
}
