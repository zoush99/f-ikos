! @expect error

program compute
  use FIKOS
  integer :: x,y,z
  x=10
  y=20
  z=x+y
  !print *, z == 30
  call assert(z /= 30)
end

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

