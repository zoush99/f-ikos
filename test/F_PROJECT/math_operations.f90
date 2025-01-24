module math_operations
    implicit none
contains
    function add(x, y)
        integer, intent(in) :: x, y
        integer :: add

        add = x / y
    end function add
    function div()
        integer :: c,d
        integer :: div
        ! Initialize variables
        c = 2
        d = c
        d = c - d
        div = c / d
    end function div
        ! External subroutine: modifies 'first' inside the subroutine
    subroutine divs3(first, second)
    implicit none
    real :: first, second, c, d, div_err
    c = 3.0
    d = 2 * c
    first = c + d
    second = c - d
    second = first + second
    div_err = first / (second - d)
    first = div_err
  end subroutine divs3
end module math_operations
