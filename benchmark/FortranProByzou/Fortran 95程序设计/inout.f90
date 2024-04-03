! @expect verified

subroutine addfives(x)
  implicit none
  real, intent(inout) :: x
  x = x + 5.0
end subroutine

real function addfivef(x) result(r)
  implicit none
  real, intent(inout) :: x
  r = x + 5.0
end function

program main
  implicit none
  real :: x = 2.0
  real :: addfivef
  real :: res
  call addfives(x)
  res = addfivef(x)
end program main

! flang -emit-llvm -S -c inout.f90 -o inout.ll
! ikos inout.ll --entry-point=MAIN_
! inout.f90: In function 'MAIN_':
! inout.f90:20:1: warning: ignored side effect of call to extern function 'fort_init'. Analysis might be unsound.
!   call addfives(x)
! ^
