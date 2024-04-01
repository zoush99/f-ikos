! @expect verified

integer function add(x)
    implicit none
    integer, intent(in) :: x
    integer :: a ! declare a variable "a"
    integer :: b
    b = 0
    a = 3  ! consider division expression as an integer operation
    write(*,*) '2.5+3.0/2.0=', A ! result: 2.5 + 1 = 3.5
    a = a / b
end function