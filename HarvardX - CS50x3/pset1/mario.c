#include <cs50.h>
#include <stdio.h>

int half_pyramid(int height)
{
    int spaces, blocks, i, j;

    spaces = height - 1;
    blocks = 2;
    for (i = 0; i < height; ++i,++blocks,--spaces) {
        for (j = 0; j < spaces; ++j) {
            printf(" ");
        }
        for (j = 0; j < blocks; ++j) {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}

int main(void)
{
    int height;
   
    printf("Height size: ");
    height = GetInt();
    while (height < 0 || height > 23) {
        printf("The lenght must be bigger than 0 and less than 23\n");
        height = GetInt();
    }
    half_pyramid(height);
    return 0;
}
