#include <stdio.h>
 int main() {
     int x=3;
     int y=6;
     int i=0;
     while(i<3){
     	y = y - 2;
     	i = i + 1;
     }
     x = x / y;
     return x;
 }
