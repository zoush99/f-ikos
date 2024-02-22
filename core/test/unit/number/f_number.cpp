//
// Created by zou on 1/7/24.
//
#define BOOST_TEST_MODULE test_f_number
#define BOOST_TEST_DYN_LINK
#include <boost/mpl/list.hpp>
#include <boost/test/unit_test.hpp>

#include <ikos/core/number/f_number.hpp>

using FNumber = ikos::core::FNumber;
using ikos::core::Signed;
using ikos::core::Unsigned;

BOOST_AUTO_TEST_CASE(test_constructor_signed) {
  BOOST_CHECK(FNumber(1,32,Signed)==FNumber(1,32,Signed));
  BOOST_CHECK(FNumber(1.2,32,Signed)==FNumber(1.2,32,Signed));
  BOOST_CHECK(FNumber(1.5,32,Signed)==FNumber(1.5,32,Signed));
  BOOST_CHECK(FNumber(1.5f,32,Signed)==FNumber(1.5f,32,Signed));
  BOOST_CHECK(FNumber(1.5,64,Signed)==FNumber(1.5,64,Signed));
  BOOST_CHECK(FNumber(0.1,64,Signed)==FNumber(0.1,64,Signed));
  BOOST_CHECK(FNumber(12,64,Signed)==FNumber(12,64,Signed));
}

BOOST_AUTO_TEST_CASE(test_zero){
  BOOST_CHECK(FNumber::zero(32,Signed)==FNumber::zero(32,Signed));
  BOOST_CHECK(FNumber::zero(32,Signed)==FNumber::zero(64,Signed));
}

BOOST_AUTO_TEST_CASE(test_assign_operation_signed) {
  BOOST_CHECK((FNumber(1,32,Signed)+=FNumber(2,32,Signed))==FNumber(3,32,Signed));
  BOOST_CHECK((FNumber(12,32,Signed)-=FNumber(2,32,Signed))==FNumber(10,32,Signed));
  BOOST_CHECK((FNumber(12,32,Signed)-=FNumber(2,32,Signed))==FNumber(10,32,Signed));
  BOOST_CHECK((FNumber(2,32,Signed)-=FNumber(12,32,Signed))==FNumber(-10,32,Signed));
  BOOST_CHECK((FNumber(12,32,Signed)*=FNumber(2,32,Signed))==FNumber(24,32,Signed));
  BOOST_CHECK((FNumber(2,32,Signed)*=FNumber(12,32,Signed))==FNumber(24,32,Signed));
  BOOST_CHECK((FNumber(2,32,Signed)*=FNumber(0,32,Signed))==FNumber(0,32,Signed));
  BOOST_CHECK((FNumber(12,32,Signed)/=FNumber(2,32,Signed))==FNumber(6,32,Signed));
  BOOST_CHECK((FNumber(3,32,Signed)/=FNumber(12,32,Signed))==FNumber(0.25,32,Signed));
  BOOST_CHECK((FNumber(1.5,32,Signed)+=FNumber(2.5,32,Signed))==FNumber(4,32,Signed));
  BOOST_CHECK((FNumber(1.5,32,Signed)-=FNumber(2.5,32,Signed))==FNumber(-1,32,Signed));
  BOOST_CHECK((FNumber(1.5,32,Signed)*=FNumber(1.5,32,Signed))==FNumber(2.25,32,Signed));
  BOOST_CHECK((FNumber(4.5f,32,Signed)/=FNumber(1.5f,32,Signed))==FNumber(3,32,Signed));
}

BOOST_AUTO_TEST_CASE(test_bit_width) {
  BOOST_CHECK(FNumber(0,32,Signed).bit_width()==32);
  BOOST_CHECK(FNumber(1.2f,32,Signed).bit_width()==32);
  BOOST_CHECK(FNumber(1.2,32,Signed).bit_width()==32);
}

BOOST_AUTO_TEST_CASE(test_sign) {
  FNumber F(10,32,Signed);
  std::cout<<F<<std::endl;
  BOOST_CHECK(FNumber(10,32,Signed).sign()==Signed);
  BOOST_CHECK(FNumber(1.2f,32,Signed).sign()==Signed);
  BOOST_CHECK(FNumber(1.2,32,Signed).sign()==Signed);
}

BOOST_AUTO_TEST_CASE(test_is_zero){
  BOOST_CHECK(FNumber(0,32,Signed).is_zero());
  BOOST_CHECK(!FNumber(12,32,Signed).is_zero());
  BOOST_CHECK(!FNumber(1.2,32,Signed).is_zero());
  BOOST_CHECK(!FNumber(1.2f,32,Signed).is_zero());
}

BOOST_AUTO_TEST_CASE(test_set_zero) {
  FNumber n(1.5, 64, Signed);
  n.set_zero();
  BOOST_CHECK(n.is_zero());

  n = FNumber (0.5f, 32, Signed);
  n.set_zero();
  BOOST_CHECK(n.is_zero());
}

BOOST_AUTO_TEST_CASE(test_minus_signed) {
  BOOST_CHECK((-FNumber(0,32,Signed))==FNumber(0,32,Signed));
  BOOST_CHECK((-FNumber(12,32,Signed))==FNumber(-12,32,Signed));
  BOOST_CHECK((-FNumber(1.2f,32,Signed))==FNumber(-1.2f,32,Signed));
  BOOST_CHECK((-FNumber(1.2,64,Signed))==FNumber(-1.2,64,Signed));
}

/*BOOST_AUTO_TEST_CASE(test_trunc_signed) {
  BOOST_CHECK(FNumber(12,32,Signed).trunc(32)==FNumber(12,32,Signed));
  BOOST_CHECK(FNumber(1.2f,32,Signed).trunc(32)==FNumber(1.2f,32,Signed));
  BOOST_CHECK(FNumber(1.2,64,Signed).trunc(32)==FNumber(1.2f,32,Signed));
}

BOOST_AUTO_TEST_CASE(test_ext_signed){
  BOOST_CHECK(FNumber(12,32,Signed).ext(32)==FNumber(12,32,Signed));
  BOOST_CHECK(FNumber(12,32,Signed).ext(64)==FNumber(12,64,Signed));
  BOOST_CHECK(FNumber(12,64,Signed).ext(64)==FNumber(12,64,Signed));
}*/

BOOST_AUTO_TEST_CASE(test_operation_signed){
  BOOST_CHECK(add(FNumber(1,32,Signed),FNumber(2,32,Signed))==FNumber(3,32,Signed));
  BOOST_CHECK(add(FNumber(1.5f,32,Signed),FNumber(2,32,Signed))==FNumber(3.5f,32,Signed));
  BOOST_CHECK(add(FNumber(1.5f,32,Signed),FNumber(2.5f,32,Signed))==FNumber(4,32,Signed));
  BOOST_CHECK(add(FNumber(1.5,64,Signed),FNumber(2.5,64,Signed))==FNumber(4,64,Signed));
  BOOST_CHECK(sub(FNumber(1,32,Signed),FNumber(2,32,Signed))==FNumber(-1,32,Signed));
  BOOST_CHECK(sub(FNumber(1.5f,32,Signed),FNumber(2,32,Signed))==FNumber(-0.5f,32,Signed));
  BOOST_CHECK(sub(FNumber(1.5f,32,Signed),FNumber(2.5f,32,Signed))==FNumber(-1,32,Signed));
  BOOST_CHECK(sub(FNumber(1.5,64,Signed),FNumber(2.5,64,Signed))==FNumber(-1,64,Signed));
  BOOST_CHECK(mul(FNumber(1,32,Signed),FNumber(2,32,Signed))==FNumber(2,32,Signed));
  BOOST_CHECK(mul(FNumber(1.5f,32,Signed),FNumber(2,32,Signed))==FNumber(3,32,Signed));
  BOOST_CHECK(mul(FNumber(1.5f,32,Signed),FNumber(2.5f,32,Signed))==FNumber(3.75f,32,Signed));
  BOOST_CHECK(mul(FNumber(1.5,64,Signed),FNumber(2.5,64,Signed))==FNumber(3.75,64,Signed));
  BOOST_CHECK(div(FNumber(1,32,Signed),FNumber(2,32,Signed))==FNumber(0.5,32,Signed));
  BOOST_CHECK(div(FNumber(1.5f,32,Signed),FNumber(2,32,Signed))==FNumber(0.75f,32,Signed));
  BOOST_CHECK(div(FNumber(1.5f,32,Signed),FNumber(3,32,Signed))==FNumber(0.5f,32,Signed));
  BOOST_CHECK(div(FNumber(1.5,64,Signed),FNumber(3,64,Signed))==FNumber(0.5,64,Signed));
}

BOOST_AUTO_TEST_CASE(test_comparision_signed){
  BOOST_CHECK(FNumber(3,32,Signed)>FNumber(2,32,Signed));
  BOOST_CHECK(FNumber(3,32,Signed)>=FNumber(2,32,Signed));
  BOOST_CHECK(FNumber(2,32,Signed)<FNumber(3,32,Signed));
  BOOST_CHECK(FNumber(2,32,Signed)<=FNumber(3,32,Signed));
  BOOST_CHECK(FNumber(2,32,Signed)!=FNumber(3,32,Signed));
  BOOST_CHECK(FNumber(3,32,Signed)!=FNumber(2,32,Signed));
  BOOST_CHECK(FNumber(3,32,Signed)==FNumber(3,32,Signed));
  BOOST_CHECK(FNumber(3,32,Signed)>FNumber(2,32,Signed));
  BOOST_CHECK(FNumber(3.5f,32,Signed)>=FNumber(2,32,Signed));
  BOOST_CHECK(FNumber(2.5f,32,Signed)<FNumber(3,32,Signed));
  BOOST_CHECK(FNumber(2.5f,32,Signed)<=FNumber(3,32,Signed));
  BOOST_CHECK(FNumber(2.5f,32,Signed)!=FNumber(3,32,Signed));
  BOOST_CHECK(FNumber(3.5f,32,Signed)!=FNumber(2,32,Signed));
  BOOST_CHECK(FNumber(3.5f,32,Signed)==FNumber(3.5f,32,Signed));
}