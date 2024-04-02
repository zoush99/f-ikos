
extern void __ikos_assert(int);
 int main() {
     int x=3;
     int y=3;
     int i=0;
     int a=1;
     int b =1;
     __ikos_assert(b!=1);
     x = x / (y-x);
     return x;
 }
