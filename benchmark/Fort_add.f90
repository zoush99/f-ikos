! @expect verified

real function add(x)
implicit none
real :: x ! declare a variable "a"
real :: y
real :: z
x=0.1;
y=x*x*x+2*x+1;
z=x*y;
end function