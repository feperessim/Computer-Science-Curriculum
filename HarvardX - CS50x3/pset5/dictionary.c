/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct dict {
         struct dict *next;
         char *word;
};

#define HASHSIZE 26
static struct dict *hashtab[HASHSIZE];

unsigned hash(const char *key)
{
    unsigned index = toupper(key[0]) - 'A';

    return index % HASHSIZE;
}

struct dict *lookup(const char *s)
{
    struct dict *np;
    
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->word) == 0) {
            return np;  /* found */
        }
    }
    return NULL;            /* not found*/
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    if (lookup(word) != NULL) {
        return true;
    }
    else {
        int i;
        for (i = 0; word[i] != '\0' && !isupper(word[i]); ++i)
            ;
        if (word[i] != '\0') {
            char newword[LENGTH + 1];
            for (i = 0; word[i] != '\0'; ++i) {
                newword[i] = tolower(word[i]);
            }
            newword[i] = '\0';
            if (lookup(newword) != NULL) {
                return true;
            }
        }
    }
    return false;
}

int getword(FILE *fp, char **s)
{
    int c, i;
    char word[LENGTH + 1];

    i = 0;
    while ((c = fgetc(fp)) != '\n' && c != EOF && i < LENGTH) {
        word[i++] = c;
    }
    word[i] = '\0';
    if (c == EOF) {
        return EOF;
    }
    if (i == 0) {
        return EOF;
    }
    if ((*s = malloc(sizeof (char) * i + 1)) == NULL) {
        return EOF;
    }
    strncpy(*s, word, i + 1);
    return i;         
}

static unsigned nofwords;

struct dict *install(char *word)
{
    struct dict *np;
    unsigned hashval;

    if ((np = lookup(word)) == NULL) {  /* Not found */
        np = malloc(sizeof(*np));
        if (np == NULL) {
            return NULL;
        }
        np->word = NULL;
        np->next = NULL;
        struct dict *hpt;
        hashval = hash(word);
        if (hashtab[hashval] != NULL) {
            for (hpt = hashtab[hashval]; hpt->next != NULL; hpt = hpt->next)
                ;
            hpt->next = np;
        }
        else {    
            np->next = hashtab[hashval];
            hashtab[hashval] = np;
       }
       np->word = word;
    }
    ++nofwords;
    return np;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE *fp;

    if ((fp = fopen(dictionary,"r")) == NULL) {  
        return false;
    }
    char *s = NULL;
    while (getword(fp, &s) != EOF) {
        if (install(s) == NULL) {
            fclose(fp);
            return false;
        }
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return nofwords;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    int i;
    struct dict *np;
    struct dict *tmp;

    for (i = 0; i < HASHSIZE; i++) {
        if (hashtab[i] != NULL) {
            np = hashtab[i];
            while (np != NULL) {
                free(np->word);
                tmp = np;
                np = np->next;
                free(tmp);
            }
        }
    }
    return true;
}
