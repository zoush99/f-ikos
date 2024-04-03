! @expect verified
! @flag --unroll=3

subroutine process_vectors(A,B,S) 
  implicit none
  integer, dimension(2) :: A, B, S
  S = A + B
end

program main
  use FIKOS
  implicit none
  integer, dimension(2) :: A = (/ 2, 3 /)
  integer, dimension(2) :: B = (/ 3, 4 /)
  integer, dimension(2) :: S
  !integer, dimension(2) :: process_vectors
  call process_vectors(A,B,S) 
  call assert(S(1) == 5)
  call assert(S(2) /= 7)
end program main

module FIKOS
  implicit none
contains
  subroutine assert(condition)
      logical, intent(in) :: condition
      
      if (.not. condition) then
          print *, 'Assertion failed!'
          stop
      endif
  end subroutine assert
end module FIKOS