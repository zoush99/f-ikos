#include <stdio.h>
 int main() {
     int x,y;
     int i=0;
     y=3;
     x=5;
     while(i<3){
        x=x+i;
        i=i+1;
     }
     y= y/(x-8);
     return y;
 }
