//
// Created by zou on 3/4/24.
//
#define BOOST_TEST_MODULE test_f_interval_number
#define BOOST_TEST_DYN_LINK
#include <boost/mpl/list.hpp>
#include <boost/test/unit_test.hpp>
#include <ikos/core/number/f_interval_number.hpp>

using FNumber = ikos::core::FNumber;
using ikos::core::Signed;
using ikos::core::Unsigned;
using FINumber = ikos::core::FINumber;

BOOST_AUTO_TEST_CASE(test_constructor_signed) {
  BOOST_CHECK(FINumber(1.2,2.2,32,Signed)==FINumber(1.2,2.2,32,Signed));
}
