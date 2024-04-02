#include <stdio.h>
 int main() {
     double x,y;
     double i;
     y=3;
     x=5;
     i=1;
     while (i<3.0){
     i = i + 2.0;
     i = i + 1.0;
     x = i + 1.0;
     }

     y= y/(i-x);
     return y;
 }
