! @expect error

pure function cap(x)
  implicit none
  integer, intent(in) :: x
  integer :: y
  integer :: cap
  y = x
  if (10 < y) then
      y = 10
  end if
  cap = y
end function


program main
  use FIKOS
  implicit none
  integer :: cap
  integer :: x
  call assert(cap(2) == 2)
  call assert(cap(15) /= 10)
  call assert(cap(x) <= 10)
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


