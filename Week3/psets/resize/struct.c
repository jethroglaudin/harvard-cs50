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
    return 0;
}