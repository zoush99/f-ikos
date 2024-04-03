! @expect error

program hello
  use FIKOS
  implicit none
  call assert(.FALSE.,"false")
end

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