#include <stdio.h>

int main()
{
    float c =2.2;
    float d =3.1;
    if (c > d)
        c = c + d;
    else
        c = c - d;

    int i;
    for (i = 0; i < 10; i++)
    {
        c = c + 1.0f;
    }
    
    c = c - 9.1;
    d = d / c;
    printf("%f\n", c);

    return d;
}
