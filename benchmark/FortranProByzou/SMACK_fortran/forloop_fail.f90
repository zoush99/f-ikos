! @expect error
! @flag --unroll=11

program main
  use FIKOS
  implicit none
  integer :: x = 0
  integer i
  do i = 1, 10
    x = x + 5
  end do
  call assert(x /= 50)
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

