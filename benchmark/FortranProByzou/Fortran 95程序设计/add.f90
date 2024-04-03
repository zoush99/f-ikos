program  ex0804
implicit none
  real::first,second
  real,external::adds
  real r
  first=1
  second=2
  call add(first,second)
  
  r=adds(first,second)
  stop
end

subroutine add(first,second)
implicit none
  real::first,second
  real::c ,d
  c = 3
  d = c
  first = c / (c - d)
  return
end

real function adds(a,b) result(r)
implicit none
real::a,b
real::c ,d
! real r
c = 3
d = 3
r = c / (c - d)
return
end
