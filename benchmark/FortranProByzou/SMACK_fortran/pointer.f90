! @expect verified

program main
  use FIKOS
  implicit none
  integer, pointer :: box
  integer, target :: x = 3
  box => x
  print *, box == 3
  call assert(box == 3)
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