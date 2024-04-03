
 int main() {
     int x=3;
     int y=3;
     int i=1;
     while(i<5){
        y = y + 3;
        i = i + 1;
     }
     x = x / (y-15);
     return x;

   //  double x=3;
   //  double y=3;
   //  double i=1;
   //  while(i<5.0){
   //     y = y + 3.0;
   //     i = i + 1.0;
   //  }
   //  x = x / (y-15.0);
   //  return x;
 }

// // Bundle
// target-endianness = little-endian
// target-pointer-size = 64 bits
// target-triple = x86_64-pc-linux-gnu

// define si32 @main() {
// #1 !entry successors={#2} {
//   si32 %.01 = 3
//   si32 %.0 = 0
// }
// #2 predecessors={#1, #3} successors={#3, #4} {
// }
// #3 predecessors={#2} successors={#2} {
//   %.0 silt 5
//   si32 %1 = %.01 sadd.nw 3
//   si32 %2 = %.0 sadd.nw 1
//   si32 %.01 = %1
//   si32 %.0 = %2
// }
// #4 !exit predecessors={#2} {
//   %.0 sige 5
//   si32 %3 = %.01 ssub.nw 18
//   si32 %4 = 3 sdiv %3
//   return %4
// }
// }


// // Bundle
// target-endianness = little-endian
// target-pointer-size = 64 bits
// target-triple = x86_64-pc-linux-gnu

// define si32 @main() {
// #1 !entry successors={#2} {
//   double %.01 = 3
//   double %.0 = 0
// }
// #2 predecessors={#1, #3} successors={#3, #4} {
// }
// #3 predecessors={#2} successors={#2} {
//   %.0 folt 5
//   double %1 = %.01 fadd 3
//   double %2 = %.0 fadd 1
//   double %.01 = %1
//   double %.0 = %2
// }
// #4 !exit predecessors={#2} {
//   %.0 fuge 5
//   double %3 = %.01 fsub 18
//   double %4 = 3 fdiv %3
//   si32 %5 = fptosi %4
//   return %5
// }
// }
