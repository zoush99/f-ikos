! @expect verified

! integer function add(x)
!     implicit none
!     integer, intent(in) :: x
!     integer :: a ! declare a variable "a"
!     integer :: b
!     b = 0
!     a = 3  ! consider division expression as an integer operation
!     write(*,*) '2.5+3.0/2.0=', A ! result: 2.5 + 1 = 3.5
!     a = a / b
! end function

! program hello
!     implicit none
!     integer::a=1
!     integer::b=2
!     integer::c=2
!     integer::div

!     a=div()
! end program hello

real function div()
implicit none
real :: a = 1
real :: b
real :: c

b=a
c = b-a
a = a / (c)
b = b + c

div = a  ! 返回值赋给函数名称相同的变量
end function div


