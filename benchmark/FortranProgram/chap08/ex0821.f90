program ex0821
  implicit none ! ����func�Ǹ��Զ��庯��
  real, intrinsic :: sin  ! ����sin�ǿ⺯��
  real :: num = 1
  call ExecFunc(num)
  call ExecFunc(sin)

  stop
end program

subroutine ExecFunc(f)
  implicit none
  real, external :: f ! ��������f�Ǹ�����
  write(*,*) f(1.0)   ! ִ�д���ĺ���f
  return
end 

real function func(num)
  implicit none
  real :: num
  num = num*2
  return
end function