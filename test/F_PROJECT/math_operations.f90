module math_operations
    implicit none
contains
    function add(x, y)
        real, intent(in) :: x, y
        real :: add

        add = x + y
    end function add
end module math_operations
