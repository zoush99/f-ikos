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

  mpq_set_d(two, 2.2);
  mpq_set_d(three, 3.2);
  FNumber tw(2.2f);
  FNumber th(3.2f);
  FNumber fo(4.2f);

  mpq_set_d(a, 0);
  mpq_set_d(b, 0);
  ap_interval_set_mpq(_sum, a, b);

  // 构建表达式 2*x
  ap_texpr0_t* expr_2x = ap_texpr0_binop(AP_TEXPR_MUL,
                                         ap_texpr0_dim(x_dim),
                                         ikos::core::numeric::apron::to_ap_expr(tw),
                                         AP_RTYPE_SINGLE,
                                         AP_RDIR_NEAREST);

  // 构建表达式 4*y
  ap_texpr0_t* expr_4y = ap_texpr0_binop(AP_TEXPR_MUL,
                                         ap_texpr0_dim(x_dim+1),
                                         ikos::core::numeric::apron::to_ap_expr(fo),
                                         AP_RTYPE_SINGLE,
                                         AP_RDIR_NEAREST);

  // 构建表达式 2*x + 4*y
  ap_texpr0_t* expr_2x_plus_4y = ap_texpr0_binop(AP_TEXPR_ADD,
                                                expr_2x,
                                                expr_4y,
                                                AP_RTYPE_SINGLE,
                                                AP_RDIR_NEAREST);

  // 构建表达式 2*x + 4*y + 3
  ap_texpr0_t* expr_2x_plus_4y_plus_3 = ap_texpr0_binop(AP_TEXPR_ADD,
                                                expr_2x_plus_4y,
                                                ikos::core::numeric::apron::to_ap_expr(th),
                                                AP_RTYPE_DOUBLE,
                                                AP_RDIR_NEAREST);

  std::cout<<"表达式的维度："<<std::endl;
  std::cout<<ap_texpr0_max_dim(expr_2x_plus_4y)<<std::endl;
  std::cout<<std::endl;
  std::cout<<std::endl;

  std::cout<<"抽象前的浮点表达式："<<std::endl;
  ap_texpr0_print(expr_2x_plus_4y_plus_3, nullptr);
  std::cout<<std::endl;
  std::cout<<std::endl;

  bool T =true;
  bool F = false;
  bool* tptr=&T;
  bool* fptr=&F;
  ap_manager_t* Man = ap_ppl_poly_manager_alloc(false);

  /// \brief Interval-linearization to a scalar coefficient
  ap_intlinearize_tcons0_array(Man, this->_inv.get(),expr_2x_plus_4y_plus_3,
                               tptr,AP_SCALAR_MPQ,AP_LINEXPR_QUASILINEAR,tptr, tptr,2, fptr);


  mpq_clears(two, three, a, b, NULL);
}

BOOST_AUTO_TEST_CASE(intervalLinearlizationC){
  // 定义变量和常量
  ap_dim_t x_dim = 0; // 假设 x 是我们要处理的变量
  mpq_t two, three, a, b;
  ap_interval_t* _sum = ap_interval_alloc();
  mpq_inits(two, three, a, b, NULL);

  mpq_set_d(two, 2);
  mpq_set_d(three, 3);
  FNumber tw(2.0f);
  FNumber th(3.0f);
  FNumber fo(4.0f);

  mpq_set_d(a, 0);
  mpq_set_d(b, 0);
  ap_interval_set_mpq(_sum, a, b);

  // 构建表达式 2*x
  ap_texpr0_t* expr_2x = ap_texpr0_binop(AP_TEXPR_MUL,
                                         ap_texpr0_dim(x_dim),
                                         ikos::core::numeric::apron::to_ap_expr(tw),
                                         AP_RTYPE_SINGLE,
                                         AP_RDIR_NEAREST);

  // 构建表达式 4*y
  ap_texpr0_t* expr_4y = ap_texpr0_binop(AP_TEXPR_MUL,
                                         ap_texpr0_dim(x_dim+1),
                                         ikos::core::numeric::apron::to_ap_expr(fo),
                                         AP_RTYPE_SINGLE,
                                         AP_RDIR_NEAREST);

  // 构建表达式 2*x + 4*y
  ap_texpr0_t* expr_2x_plus_4y = ap_texpr0_binop(AP_TEXPR_ADD,
                                                 expr_2x,
                                                 expr_4y,
                                                 AP_RTYPE_SINGLE,
                                                 AP_RDIR_NEAREST);

  // 构建表达式 2*x + 4*y + 3
  ap_texpr0_t* expr_2x_plus_4y_plus_3 = ap_texpr0_binop(AP_TEXPR_ADD,
                                                        expr_2x_plus_4y,
                                                        ikos::core::numeric::apron::to_ap_expr(th),
                                                        AP_RTYPE_SINGLE,
                                                        AP_RDIR_NEAREST);

/*  std::cout<<"表达式的维度："<<std::endl;
  std::cout<<ap_texpr0_max_dim(expr_2x_plus_4y)<<std::endl;
  std::cout<<std::endl;
  std::cout<<std::endl;*/

  ikos::core::numeric::apron::abstractExpr(expr_2x_plus_4y_plus_3, _sum);
  ikos::core::numeric::apron::abstractConstant(expr_2x_plus_4y_plus_3,_sum);
  ap_texpr0_print(expr_2x_plus_4y_plus_3, nullptr);

}


