#include <cs50.h>
#include <stdio.h>

#define MAX_COIN 4

int count_change_coins(float value)
{
    float coins[] = {0.25, 0.10, 0.05, 0.01};
    float current_value;
    int count_change, i, j, k;
    int best_possibility = 0;

    for (i = 0; i < MAX_COIN; ++i) {
        for (j = 0; j < MAX_COIN; ++j) {
            k = j;
            current_value = count_change = 0;
            while (current_value < value && k < MAX_COIN) {
                if (current_value + coins[k] <= value) {
                    ++count_change;
                    current_value += coins[k];
                }
                else {
                    ++k;
                }
            }
            if (best_possibility == 0 || best_possibility > count_change) {
                best_possibility = count_change;        
            }    
        }
    }
    return best_possibility;
}
int main(void)
{
    int possibilities;
    float value;

    do {
        printf("How much change is owed?\n");
        value = GetFloat();

    } while (value < 0);
    possibilities = count_change_coins(value);
    printf("%d\n", possibilities);
    return 0;
}
