! math_operations.h
! This file declares the interface for the math_operations module
module math_operations
    implicit none
contains
    function add(x, y)
        integer, intent(in) :: x, y
        real :: add
    end function add
    function div()
        integer :: x, y
        integer :: div
    end function div
    subroutine divs3(first, second)
        real :: first, second, c, d, div_err
    end subroutine divs3
end module math_operations
