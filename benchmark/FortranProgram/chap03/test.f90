integer,target::target(2)=(/1,2/)
logical:: l1,l2
type t
  integer,pointer :: ptr
end type
type(t) a(2)
a(1)%ptr => target(1)
a(2)%ptr => target(2)
l1 = associated(a(1)%ptr,target(1))
l2 = associated(a(2)%ptr,target(2))
end