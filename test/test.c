#include <stdio.h>

int main()
{
    float a,b;
    a = 1.100009;
    b = 1.10001;
    a = a - b;
    b = a + b;
    b = b / a;
    return b;
}
