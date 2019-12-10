#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val1;
    int val2;
} MYSTRUCT;

int main(void)
{
    MYSTRUCT item;
    item.val1 = 18;
    item.val2 = 38;
    printf("%i\n", item.val2);

    MYSTRUCT structArray[5];
    structArray[0].val1 = 48;
    structArray[0].val2 = 88;
    structArray[3].val2 = 33;
    printf("%i\n", structArray[0].val1);
    return 0;
}