! program ex0405
!   integer a
!   integer b
!   integer c
!   a=2+2*4-3
!   b=3
!   c=0
!   a=a/c
!   ! write(*,*) "2+2*4-3=",a
! stop
! end

real function div()
implicit none
real a
real b
real c
a=2+2*4-3
b=3
c=1
a=a/(c-1)
div =a
end function