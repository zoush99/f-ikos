program main
    use math_operations
    implicit none
    integer :: a, b, result
    integer :: c,d,r
    real :: first,second,rf
    ! real,external::divs3
    a = 1
    b = 2
    b = 2 * a - b

    result = div()
    print *,result
    
    c = 1
    d = 2
    d = 2 * c - d
    r = c / d
    print *,r

    first = 2
    second = 2
    call divs3(first, second)
end program main
