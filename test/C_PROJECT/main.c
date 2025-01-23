#include <stdio.h>
#include "utils.h"

int main() {
    int result = add(3, 5);
    int i;
    int j;
    i = 1;
    j = 2;
    result = i / (2*i-j);
    printf("The sum of 3 and 5 is: %d\n", result);
    return 0;
}
