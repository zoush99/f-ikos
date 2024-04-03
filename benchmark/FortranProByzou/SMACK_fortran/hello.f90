! @expect verified

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

program hello
  use FIKOS
  implicit none
  call assert(.true.)
end
