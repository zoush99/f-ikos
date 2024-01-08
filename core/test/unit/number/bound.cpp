//
// Created by zou on 1/8/24.
//
#define BOOST_TEST_MODULE test_bound
#define BOOST_TEST_DYN_LINK
#include <boost/mpl/list.hpp>
#include <boost/test/unit_test.hpp>

#include <ikos/core/number/bound.hpp>

using FNumber = ikos::core::FNumber;
using ikos::core::Signed;
using ikos::core::Unsigned;

BOOST_AUTO_TEST_CASE(test_constructor_signed) {
  BOOST_CHECK(FNumber(1,32,Signed)==FNumber(1,32,Signed));

}
