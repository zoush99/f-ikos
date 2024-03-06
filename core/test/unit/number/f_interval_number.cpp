//
// Created by zou on 3/4/24.
//
#include <boost/test/tools/old/interface.hpp>
#define BOOST_TEST_MODULE test_f_interval_number
#define BOOST_TEST_DYN_LINK
#include <boost/mpl/list.hpp>
#include <boost/test/unit_test.hpp>
#include <ikos/core/number/bound.hpp>
#include <ikos/core/number/f_interval_number.hpp>

using FNumber = ikos::core::FNumber;
using FBound = ikos::core::Bound< FNumber >;
using ikos::core::Signed;
using ikos::core::Unsigned;
using FINumber = ikos::core::FINumber;

BOOST_AUTO_TEST_CASE(test_constructor_signed) {
  FNumber f1(1.2);
  FNumber f2(2.4);
  FBound fb1(f1);
  FBound fb2(f2);
  FINumber fi1(f1, f2);
  BOOST_CHECK(FINumber(1.2, 2.2, 64, Signed) == FINumber(1.2, 2.2, 64, Signed));
  BOOST_CHECK(FINumber() == FINumber(1, 1, 32, Signed));
  BOOST_CHECK(FINumber(3, 32, Signed) == FINumber(3, 3, 32, Signed));
  BOOST_CHECK(FINumber(1.3, 64, Signed) == FINumber(1.3, 1.3, 64, Signed));
  BOOST_CHECK(FINumber(1.3, 13, 64, Signed) == FINumber(1.3, 13, 64, Signed));
  BOOST_CHECK(FINumber(1.2) == FINumber(1.2, 1.2, 64, Signed));
  BOOST_CHECK(FINumber(1.2, 1.2) == FINumber(1.2, 1.2, 64, Signed));
  BOOST_CHECK(FINumber(f1, f2, 64, Signed) == FINumber(f1, f2, 64, Signed));
  BOOST_CHECK(FINumber(f1, f2) == FINumber(f1, f2, 64, Signed));
  BOOST_CHECK(FINumber(f1 + f1, f2) == FINumber(f2, f2, 64, Signed));
  BOOST_CHECK(FINumber(fb1, fb2, 64, Signed) == FINumber(fb1, fb2, 64, Signed));
  BOOST_CHECK(FINumber(fb1, fb2) == FINumber(fb1, fb2, 64, Signed));
  BOOST_CHECK(FINumber(FINumber(1.2, 1.3)) == FINumber(1.2, 1.3, 64, Signed));
  BOOST_CHECK(FINumber(FINumber(1.3, 1.2)) == FINumber(1.3, 1.2, 64, Signed));
  BOOST_CHECK(FINumber(std::move(fi1)) == FINumber(1.2, 2.4, 64, Signed));
}

BOOST_AUTO_TEST_CASE(test_top_bottom) {
  BOOST_CHECK(FINumber(1, -1).is_bottom() == true);
  BOOST_CHECK(
      FINumber(FBound::minus_infinity(), FBound::plus_infinity()).is_top() ==
      true);
}

BOOST_AUTO_TEST_CASE(test_lb_ub_zero) {
  BOOST_CHECK(FINumber(1.2, 2.4, 64, Signed).lb() == FBound(1.2));
  BOOST_CHECK(FINumber(1.2, 2.4, 64, Signed).ub() == FBound(2.4));
  BOOST_CHECK(FINumber(0, 0, 32, Signed) == FINumber::zero(32, Signed));
}

BOOST_AUTO_TEST_CASE(test_assign) {
  FINumber fi1(1.2, 2.4, 64, Signed);
  FINumber fi2(2.4, 4.8, 64, Signed);
  FINumber fi = fi1;
  BOOST_CHECK(FINumber(1.2, 2.4, 64, Signed) == fi);
  BOOST_CHECK(FINumber(1.2, 2.4, 64, Signed) == (fi = std::move(fi1)));
  BOOST_CHECK(FINumber(1.2, 1.2) == (fi = 1.2));
  BOOST_CHECK(FINumber(fi2) ==
              (FINumber(1.2, 2.4, 64, Signed) += FINumber(fi1)));
  BOOST_CHECK(FINumber(0., 1.2, 64, Signed) ==
              (FINumber(2.4, 2.4, 64, Signed) -= FINumber(fi1)));
  BOOST_CHECK(FINumber(-20, 15, 32, Signed) ==
              (FINumber(-4, 3, 32, Signed) *= FINumber(-3, 5, 32, Signed)));
  BOOST_CHECK(FINumber(0.5f, 2.0f, 32, Signed) == (FINumber(2, 4, 32, Signed) /=
              FINumber(2, 4, 32, Signed)));
}

BOOST_AUTO_TEST_CASE(test_sign_bitwidth) {
  BOOST_CHECK(FINumber(1.2, 2.4, 64, Signed).sign() == Signed);
  BOOST_CHECK(FINumber(1.2, 2.4).sign() == Signed);
  BOOST_CHECK(FINumber(1.2, 2.4, 64, Signed).bit_width() == 64);
  BOOST_CHECK(FINumber(1.2, 2.4).bit_width() == 64);
  BOOST_CHECK(FINumber(1.2, 2.4, 64, Signed).is_signed() == true);
  BOOST_CHECK(FINumber(1.2, 2.4, 64, Signed).is_unsigned() == false);
}

BOOST_AUTO_TEST_CASE(test_zero_unary) {
  BOOST_CHECK(FINumber(0, 0, 32, Signed).is_zero() == true);
  BOOST_CHECK(FINumber(0, 10, 32, Signed).set_zero() ==
              FINumber(0, 0, 32, Signed));
  BOOST_CHECK(FINumber(1.2, 2.4, 64, Signed) ==
              -FINumber(-2.4, -1.2, 64, Signed));
  BOOST_CHECK(FINumber(1.2, 1.2, 64, Signed).singleton() == FBound(1.2));
  BOOST_CHECK(FINumber(1.2, 2.4, 64, Signed).contains(1.5) == true);
  BOOST_CHECK(FINumber(1.2, 2.4, 64, Signed).contains(2.5) == false);
}

BOOST_AUTO_TEST_CASE(test_binary_operation) {
  FINumber fi1(1, 2);
  FINumber fi2(2, 4);
  BOOST_CHECK(FINumber(3, 6) == (FINumber(1, 2) + FINumber(2, 4)));
  BOOST_CHECK(FINumber(0, 3) == (fi2 - fi1));
  BOOST_CHECK(FINumber(2, 8) == (fi2 * fi1));
  BOOST_CHECK(FINumber(1, 4) == (fi2 / fi1));
  BOOST_CHECK(FINumber(0.25f, 1) == (fi1 / fi2));
}

BOOST_AUTO_TEST_CASE(test_comparasion) {
  BOOST_CHECK(FINumber(1.2, 2.4) == FINumber(1.2, 2.4));
  BOOST_CHECK(FINumber(1.2, 2.5) != FINumber(1.2, 2.4));
  BOOST_CHECK(FINumber(1.1, 2.5) > FINumber(1.2, 2.4));
  BOOST_CHECK(FINumber(1.1, 2.5) >= FINumber(1.2, 2.4));
  BOOST_CHECK(FINumber(1.2, 2.4) >= FINumber(1.2, 2.4));
  BOOST_CHECK(FINumber(1.1, 2.4) >= FINumber(1.2, 2.4));
  BOOST_CHECK(FINumber(1.2, 2.4) < FINumber(1., 2.5));
  BOOST_CHECK(FINumber(1.2, 2.4) <= FINumber(1., 2.5));
  BOOST_CHECK(FINumber(1.2, 2.4) <= FINumber(1.2, 2.4));
  BOOST_CHECK(FINumber(1.2, 2.4) <= FINumber(1.2, 2.5));
}

BOOST_AUTO_TEST_CASE(test_float) {
  float x=1.2;
  double y=1.2;
//  ikos::core::detail::find_nearest_floats(x);
  ikos::core::detail::find_next_value_down(y);
  ikos::core::detail::find_next_value_up(y);
}