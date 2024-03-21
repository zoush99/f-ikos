#define BOOST_TEST_MODULE test_apron_source
#define BOOST_TEST_DYN_LINK
#include <boost/mpl/list.hpp>
#include <boost/test/unit_test.hpp>

#include <ikos/core/domain/numeric/apron.hpp>

#include <ikos/core/example/variable_factory.hpp>
#include <ikos/core/number/z_number.hpp>
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

/// polka_polyhedra.cpp
using VariableFactory = ikos::core::example::VariableFactory;
using Variable = ikos::core::example::VariableFactory::VariableRef;
using VariableExpr = ikos::core::VariableExpression< FNumber, Variable >;
using BinaryOperator = ikos::core::numeric::BinaryOperator;
using Bound = ikos::core::FBound;
using Interval = ikos::core::numeric::FInterval;
using Congruence = ikos::core::numeric::FCongruence;
using IntervalCongruence = ikos::core::numeric::IntervalCongruence< FNumber >;
using ApronDomain = ikos::core::numeric::
    ApronDomain< ikos::core::numeric::apron::PplPolyhedra, FNumber, Variable >;

BOOST_AUTO_TEST_CASE(to_ap_expr_FNumber) {
  float f=0.1f;
  double g=0.1;
  FNumber _f(f);
  FNumber _g(g);
//  std::cout.precision(30);
//  std::cout<<g<<std::endl;
  ap_texpr0_t* _a(ikos::core::numeric::apron::to_ap_expr(_f));
  ap_texpr0_print(_a, nullptr);
  std::cout<<std::endl;
  ap_texpr0_t* _b(ikos::core::numeric::apron::to_ap_expr(_g));
  ap_texpr0_print(_b, nullptr);
}

BOOST_AUTO_TEST_CASE(function_abstractExpr) {
  mpq_t a,b;
  ap_texpr0_t * expr;
  ap_interval_t* _sum=ap_interval_alloc();
  mpq_inits(a,b,NULL);

  // Try using ap_texpr0_t*
  mpq_set_d(a,1.0);
  mpq_set_d(b,2.0);
  expr= ap_texpr0_cst_interval_mpq(a,b);
  ap_texpr0_print(expr, nullptr);
  std::cout<<std::endl;

  // Try using ap_interval_t*
  ap_interval_set_mpq(_sum,a,b);
  ap_interval_print(_sum);
  std::cout<<std::endl;

  // Try using abstractExpr
  ikos::core::numeric::apron::abstractExpr(expr,_sum);
  mpq_clears(a,b,NULL);
}
