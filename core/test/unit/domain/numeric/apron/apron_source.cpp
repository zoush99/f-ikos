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
  float f = 0.1f;
  double g = 0.1;
  FNumber _f(f);
  FNumber _g(g);
  //  std::cout.precision(30);
  //  std::cout<<g<<std::endl;
  ap_texpr0_t* _a(ikos::core::numeric::apron::to_ap_expr(_f));
  ap_texpr0_print(_a, nullptr);
  std::cout << std::endl;
  ap_texpr0_t* _b(ikos::core::numeric::apron::to_ap_expr(_g));
  ap_texpr0_print(_b, nullptr);
}

BOOST_AUTO_TEST_CASE(function_abstractExpr) {
  mpq_t a, b;
  ap_texpr0_t* expr;
  ap_interval_t* _sum = ap_interval_alloc();
  mpq_inits(a, b, NULL);

  // Try using ap_texpr0_t*
  mpq_set_d(a, 0.1);
  mpq_set_d(b, 0.2);
  expr = ap_texpr0_cst_interval_mpq(a, b);
  std::cout << "expr: " << std::endl;
  ap_texpr0_print(expr, nullptr);
  std::cout << std::endl;

  // Try using ap_interval_t*
  mpq_set_d(a, 0);
  mpq_set_d(b, 0);
  ap_interval_set_mpq(_sum, a, b);
  std::cout << "_sum: " << std::endl;
  ap_interval_print(_sum);
  std::cout << std::endl;

  // Try using abstractExpr
  ikos::core::numeric::apron::abstractExpr(expr, _sum);
  std::cout << "_sum: " << std::endl;
  ap_interval_print(_sum);
  mpq_clears(a, b, NULL);
}

BOOST_AUTO_TEST_CASE(function_abstractExpr_NODE) {
  VariableFactory vfac;
  Variable x(vfac.get("x"));
  Variable y(vfac.get("y"));

  auto inv1 = ApronDomain::top();
  /// bugs here!!! function intervalLinearization
    inv1.set(x, Interval(0));
    BOOST_CHECK(inv1.leq(ApronDomain::top()));
    BOOST_CHECK(!inv1.leq(ApronDomain::bottom()));
}

BOOST_AUTO_TEST_CASE(check_mul_var_expr) {
  // 定义变量和常量
  ap_dim_t x_dim = 0; // 假设 x 是我们要处理的变量
  mpq_t two, three, a, b;
  ap_interval_t* _sum = ap_interval_alloc();
  mpq_inits(two, three, a, b, NULL);

  mpq_set_d(two, 2);
  mpq_set_d(three, 3);
  FNumber tw(2.0f);
  FNumber th(3.0f);

  mpq_set_d(a, 0);
  mpq_set_d(b, 0);
  ap_interval_set_mpq(_sum, a, b);

  // 构建表达式 2*x
  ap_texpr0_t* expr_2x = ap_texpr0_binop(AP_TEXPR_MUL,
                                         ap_texpr0_dim(x_dim),
                                         ikos::core::numeric::apron::to_ap_expr(tw),
                                         AP_RTYPE_SINGLE,
                                         AP_RDIR_NEAREST);

  // 构建表达式 2*x + 3
  ap_texpr0_t* expr_2x_plus_3 = ap_texpr0_binop(AP_TEXPR_ADD,
                                                expr_2x,
                                                ikos::core::numeric::apron::to_ap_expr(th),
                                                AP_RTYPE_SINGLE,
                                                AP_RDIR_NEAREST);

  ikos::core::numeric::apron::abstractExpr(expr_2x_plus_3, _sum);
  std::cout << "_sum: " << std::endl;
  ap_interval_print(_sum);

  mpq_clears(two, three, a, b, NULL);
}

/// bugs here!!!
BOOST_AUTO_TEST_CASE(leq) {
  VariableFactory vfac;
  Variable x(vfac.get("x"));
  Variable y(vfac.get("y"));
  Variable z(vfac.get("z"));
  Variable a(vfac.get("a"));
  Variable b(vfac.get("b"));

  BOOST_CHECK(ApronDomain::bottom().leq(ApronDomain::top()));
  BOOST_CHECK(ApronDomain::bottom().leq(ApronDomain::bottom()));
  BOOST_CHECK(!ApronDomain::top().leq(ApronDomain::bottom()));
  BOOST_CHECK(ApronDomain::top().leq(ApronDomain::top()));

  auto inv1 = ApronDomain::top();
  inv1.set(x, Interval(0));
  BOOST_CHECK(inv1.leq(ApronDomain::top()));
  BOOST_CHECK(!inv1.leq(ApronDomain::bottom()));

  auto inv2 = ApronDomain::top();
  inv2.set(x, Interval(Bound(-1), Bound(1)));
  BOOST_CHECK(inv2.leq(ApronDomain::top()));
  BOOST_CHECK(!inv2.leq(ApronDomain::bottom()));
  BOOST_CHECK(inv1.leq(inv2));
  BOOST_CHECK(!inv2.leq(inv1));

  auto inv3 = ApronDomain::top();
  inv3.set(x, Interval(0));
  inv3.set(y, Interval(Bound(-1), Bound(1)));
  BOOST_CHECK(inv3.leq(ApronDomain::top()));
  BOOST_CHECK(!inv3.leq(ApronDomain::bottom()));
  BOOST_CHECK(inv3.leq(inv1));
  BOOST_CHECK(!inv1.leq(inv3));

  auto inv4 = ApronDomain::top();
  inv4.set(x, Interval(0));
  inv4.set(y, Interval(Bound(0), Bound(2)));
  BOOST_CHECK(inv4.leq(ApronDomain::top()));
  BOOST_CHECK(!inv4.leq(ApronDomain::bottom()));
  BOOST_CHECK(!inv3.leq(inv4));
  BOOST_CHECK(!inv4.leq(inv3));

  auto inv5 = ApronDomain::top();
  inv5.set(x, Interval(0));
  inv5.set(y, Interval(Bound(0), Bound(2)));
  inv5.set(z, Interval(Bound::minus_infinity(), Bound(0)));
  BOOST_CHECK(inv5.leq(ApronDomain::top()));
  BOOST_CHECK(!inv5.leq(ApronDomain::bottom()));
  BOOST_CHECK(!inv5.leq(inv3));
  BOOST_CHECK(!inv3.leq(inv5));
  BOOST_CHECK(inv5.leq(inv4));
  BOOST_CHECK(!inv4.leq(inv5));

  inv1.set_to_top();
  inv2.set_to_top();
  inv1.assign(x, 1);
  BOOST_CHECK(inv1.leq(inv2));

  inv2.add(VariableExpr(x) <= 1);
  BOOST_CHECK(inv1.leq(inv2)); // {x = 1} <= {x <= 1}

  inv2.set_to_top();
  inv2.add(VariableExpr(x) <= 0);
  BOOST_CHECK(!inv1.leq(inv2)); // not {x = 1} <= {x <= 0}

  inv1.assign(y, 2);
  inv2.set_to_top();
  inv2.add(VariableExpr(x) <= 1);
  BOOST_CHECK(inv1.leq(inv2)); // {x = 1, y = 2} <= {x <= 1}

  inv2.add(VariableExpr(z) <= 4);
  BOOST_CHECK(!inv1.leq(inv2)); // not {x = 1, y = 2} <= {x <= 1, z <= 4}

  inv1.set_to_top();
  inv2.set_to_top();

  inv1.assign(x, 1);
  inv1.add(VariableExpr(y) <= 2);
  inv1.assign(z, 3);
  inv1.add(VariableExpr(a) >= 4);
  inv1.assign(b, 5);

  inv2.add(VariableExpr(y) <= 3);
  inv2.add(VariableExpr(a) >= 1);
  inv2.assign(z, 3);
  inv2.set(x, Interval(Bound(-1), Bound(1)));

  // {x = 1, y <= 2, z = 3, a >= 4, b = 5} <= {-1 <= x <= 1, y <= 3, z = 3, a >=
  // 1}
  BOOST_CHECK(inv1.leq(inv2));

  inv2.add(VariableExpr(a) >= 5);
  // {x = 1, y <= 2, z = 3, a >= 4, b = 5} <= {-1 <= x <= 1, y <= 3, z = 3, a >=
  // 5}
  BOOST_CHECK(!inv1.leq(inv2));
}
