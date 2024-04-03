! @expect verified
module FIKOS
  implicit none

  character(len=100) :: error_message

contains

  subroutine assert(condition, message)
    logical, intent(in) :: condition
    character(len=*), intent(in) :: message

    if (.not. condition) then
      error_message = message
      call print_error()
      stop
    end if
  end subroutine assert

  subroutine print_error()
    print *, 'Assertion failed: ', error_message
  end subroutine print_error

end module FIKOS

program main
  use FIKOS
  implicit none
  type Location
    integer x
  end type Location

  type(Location) :: p
  p = Location(3)
  !print *, p%x == 3
  call assert(p%x == 3,"fail")
end program main
