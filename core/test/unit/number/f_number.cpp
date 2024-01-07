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
  FNumber m(1.5f,32,Signed);
  FNumber n(0.5f,32,Signed);
  BOOST_CHECK(FNumber(2.0f,32,Signed)==(m+n));
  BOOST_CHECK(FNumber(3.0f,32,Signed)==(m/n));
}
