! @expect verified
! @flag --unroll=10

recursive function fib(n)
  implicit none
  integer, intent(in) :: n
  integer :: fib
  if (n <= 0) then
    fib = 0
  else if (n == 1) then
    fib = 1
  else 
    fib = fib(n - 1) + fib(n - 2)
  end if
end function

program main
  use FIKOS
  implicit none
  integer :: fib
  !print *, fib(5) == 5
  !print *, fib(6) == 8 
  integer :: z
  !z = fib(2)
  !call assert(z > 18)
  call assert(fib(5) == 5)
  call assert(fib(6) == 8)
end program main

module FIKOS
  implicit none
contains
  subroutine assert(condition)
      logical, intent(in) :: condition
      
      if (.not. condition) then
          print *, 'Assertion failed!'
          stop
      endif
  end subroutine assert
end module FIKOS

