! math_operations.h
! This file declares the interface for the math_operations module
module math_operations
    implicit none
contains
    function add(x, y)
        real, intent(in) :: x, y
        real :: add
    end function add
end module math_operations
