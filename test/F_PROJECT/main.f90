program main
    use math_operations
    implicit none
    real :: a, b, result

    ! Initialize variables
    a = 5.0
    b = 3.0

    ! Call the addition function
    result = add(a, b)
    print *, "The sum of ", a, " and ", b, " is: ", result
end program main
