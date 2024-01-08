//
// Created by zou on 1/8/24.
//
#define BOOST_TEST_MODULE test_bound
#define BOOST_TEST_DYN_LINK
#include <boost/mpl/list.hpp>
#include <boost/test/unit_test.hpp>

#include <ikos/core/number/bound.hpp>

using ZNumber=ikos::core::ZNumber;
using BoundZ = ikos::core::Bound<ZNumber>;

using FNumber=ikos::core::FNumber;
using BoundF = ikos::core::Bound<FNumber>;

using ikos::core::Signed;
using ikos::core::Unsigned;

BOOST_AUTO_TEST_CASE(test_constructor_signed) {
  BoundZ z(1);
  BoundF f(1.2);
  ZNumber Z(1);
  FNumber F(1.2);
  BoundZ Zz(Z);
  BoundF Ff(F);
  BOOST_CHECK(BoundF(1.2)==BoundF(1.2));
}
