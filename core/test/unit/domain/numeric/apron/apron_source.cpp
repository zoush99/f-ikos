#define BOOST_TEST_MODULE test_apron_source
#define BOOST_TEST_DYN_LINK
#include <boost/mpl/list.hpp>
#include <boost/test/unit_test.hpp>

#include <ikos/core/domain/numeric/apron.hpp>

/*
using ZNumber = ikos::core::ZNumber;
using VariableFactory = ikos::core::example::VariableFactory;
using Variable = ikos::core::example::VariableFactory::VariableRef;
using VariableExpr = ikos::core::VariableExpression< ZNumber, Variable >;
using BinaryOperator = ikos::core::numeric::BinaryOperator;
using Bound = ikos::core::ZBound;
using Interval = ikos::core::numeric::ZInterval;
using Congruence = ikos::core::numeric::ZCongruence;
using IntervalCongruence = ikos::core::numeric::IntervalCongruence< ZNumber >;
using IntervalDomain = ikos::core::numeric::IntervalDomain< ZNumber, Variable >;
*/

using FNumber = ikos::core::FNumber;

BOOST_AUTO_TEST_CASE(is_top_and_bottom) {
  FNumber _f(0.1f);
  ap_texpr0_t* _a = ikos::core::numeric::apron::to_ap_expr(_f);
  ap_texpr0_print(_a, nullptr);
}
