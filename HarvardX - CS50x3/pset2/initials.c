#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

#define MAXNAME 50

string get_name(void)
{
    return GetString();
}

void print_initials(string name)
{
    int i = 0;

    if (isupper(name[0])) {
        printf("%c", name[0]);
    }
    else {
        printf("%c", toupper(name[0]));
    }
    for (i = 0; name[i] != '\0'; ++i) {
        if (name[i] == ' ') {
            if (name[i+1] != '\0') {
                printf("%c", (isupper(name[i+1]) != 0) ? name[i+1] : toupper(name[i+1]));
            }    
        }
    }
    putchar('\n');
    return;
}

int main(void)
{
    string name = get_name();
    print_initials(name);
    return 0;
}
