program main
    implicit none
    integer(kind=4) i1      !The integer supports 4, 2, and on some occasions 1, but the range is small. It is not recommended to use
    integer(kind=2) i2
    integer(kind=1) i3
    real(kind=8) r1
    real(kind=4) r2
    !real(kind=2) r3         !Syntax error, real only supports 8 and 4
    complex(kind=4) c1
    character(len=20) s1        !kind means the length of space requested for the string
    logical l1      !.true. or .false.
    i1 = 10
    r1 = 1.0        !When defined as real, if there is no number in the decimal place, it is still necessary to add the decimal place 0
    c1 = (1.0,2.0)      !The first bit indicates the real part and the second bit indicates the imaginary part
    s1 = "Fortran"
    l1 = .true.
    i3 =  i1 / (2 * i2)
    !write (*,*) s1
end program main