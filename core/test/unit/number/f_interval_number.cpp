//
// Created by zou on 3/4/24.
//
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
  FINumber fi1(f1,f2);
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
  BOOST_CHECK(FINumber(FINumber(1.2,1.3)) == FINumber(1.2,1.3, 64, Signed));
  BOOST_CHECK(FINumber(FINumber(1.3,1.2)) == FINumber(1.3,1.2, 64, Signed));
  BOOST_CHECK(FINumber(std::move(fi1)) == FINumber(1.2,2.4, 64, Signed));
}

BOOST_AUTO_TEST_CASE(test_top_bottom){
  BOOST_CHECK(FINumber(1,-1).is_bottom()== true);
  BOOST_CHECK(FINumber(FBound::minus_infinity(),FBound::plus_infinity()).is_top()== true);
}