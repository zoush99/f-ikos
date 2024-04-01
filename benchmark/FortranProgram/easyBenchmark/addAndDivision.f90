real function add(a)
  implicit none
  real, intent(in) :: a
  real :: a ! declare a variable "a"
  real :: b
  b = 0
  a = 2.5+3/2  ! consider division expression as an integer operation
  write(*,*) '2.5+3.0/2.0=', A ! result: 2.5 + 1 = 3.5
  a = a / b
end function
