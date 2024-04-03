! @expect verified
! @flag --unroll=11

real function divf() result(r)
implicit none
real :: x = 1
real ::i=1
real ::t=5
do while(i<=t)
  x = x + t
  i = i + t
end do
! divide by zero
r = x / (x - 6)
end function

subroutine divs(res)
  implicit none
  real:: res
  real::x=1
  real::i=1
  real::t=5
  do while(i<t)
    x = x + t
    i = i + t
  end do
  ! divide by zero
  res = x / (x - 6)
  return
end subroutine

program main
  implicit none
  real resfunc
  real ressubr
  real,external::divf
  resfunc = divf()
  call divs(ressubr)
end program main

! flang -emit-llvm -S -c forloop.f90 -o forloop.ll
! ikos forloop.ll --entry-point=MAIN_ 

! # Results
! forloop.f90: In function 'divf_':
! forloop.f90:9:1: warning: expression '*((float*)(&((int8_t*)(&.STATICS1))[4]))' might be uninitialized
! do while(i<=t)
! ^
! forloop.f90: In function 'divf_':
! forloop.f90:9:1: warning: expression '*((float*)(&((int8_t*)(&.STATICS1))[4]))' might be uninitialized
! do while(i<=t)
! ^
! forloop.f90: In function 'divf_':
! forloop.f90:10:1: warning: expression '*((float*)(&((int8_t*)(&.STATICS1))[8]))' might be uninitialized
!   x = x + t
! ^
! forloop.f90: In function 'divf_':
! forloop.f90:11:1: warning: expression '*((float*)(&((int8_t*)(&.STATICS1))[4]))' might be uninitialized
!   i = i + t
! ^
! forloop.f90: In function 'divf_':
! forloop.f90:14:1: warning: expression '*((float*)(&((int8_t*)(&.STATICS1))[8]))' might be uninitialized
! r = x / (x - 6)
! ^
! forloop.f90: In function 'divf_':
! forloop.f90:14:1: warning: expression '*((float*)(&((int8_t*)(&.STATICS1))[8]))' might be uninitialized
! r = x / (x - 6)
! ^
! Traceback (most recent call last):
!   File "/home/zou/Documents/f-ikos/install/bin/ikos", line 55, in <module>
!     ikos.analyzer.main(sys.argv)
!   File "/home/zou/Documents/f-ikos/install/libexec/lib/python3.8/site-packages/ikos/analyzer.py", line 1107, in main
!     formatter.format(rep)
!   File "/home/zou/Documents/f-ikos/install/libexec/lib/python3.8/site-packages/ikos/report.py", line 1163, in format
!     super(AutoFormatter, self).format(report)
!   File "/home/zou/Documents/f-ikos/install/libexec/lib/python3.8/site-packages/ikos/report.py", line 762, in format
!     message = generate_message(statement_report, self.verbosity)
!   File "/home/zou/Documents/f-ikos/install/libexec/lib/python3.8/site-packages/ikos/report.py", line 1184, in generate_message
!     return GENERATE_MESSAGE_MAP[report.kind](report, verbosity)
!   File "/home/zou/Documents/f-ikos/install/libexec/lib/python3.8/site-packages/ikos/report.py", line 1376, in generate_division_by_zero_message
!     s += ' (%s)' % interval.to_constraints('divisor')
!   File "/home/zou/Documents/f-ikos/install/libexec/lib/python3.8/site-packages/ikos/abs_int.py", line 187, in to_constraints
!     assert not self.is_bottom()
! AssertionError
