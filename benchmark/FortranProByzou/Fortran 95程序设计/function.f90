! @expect verified

pure function cap(x)
  implicit none
  real, intent(in) :: x
  real :: y
  real :: cap
  y = x
  if (10.0 < y) then
    y = 10.0
  else if (10.0 > y) then
    y = 20.0
  else
    y = y / (y-x)
  end if
  cap = y
end function

program main
  implicit none
  real :: cap
  real :: x
  ! divide by zero
  x=cap(10)
end program main


! flang -emit-llvm -S -c function.f90 -o function.ll
! ikos function.ll --entry-point=MAIN_ 

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
