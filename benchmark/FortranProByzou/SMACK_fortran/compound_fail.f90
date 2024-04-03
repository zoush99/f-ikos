! @expect error

program main
  use FIKOS
  implicit none
  type Location
    integer x
    integer y
  end type Location

  type(Location) :: p
  p = Location(2,3)
  !print *, p%x == 3
  call assert(p%x /= 2)
  call assert(p%y == 3)
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

