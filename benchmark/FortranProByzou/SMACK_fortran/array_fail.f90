! @expect error

program main
  use FIKOS
  implicit none
  integer, dimension(1) :: array = (/ 0 /)
  !print *, array(1) == 3
  array(1) = 3
  call assert(array(1) /= 3)
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

