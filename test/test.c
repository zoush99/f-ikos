#include <stdio.h>

int main()
{
    int c =2;
    int d =3;
    if (c > d)
        c = c + d;
    else
        c = c - d;

    int i;
    for (i = 0; i < 10; i++)
    {
        c = c + 1;
    }
    
    c = c - 9;
    d = d / c;

    return d;
}
