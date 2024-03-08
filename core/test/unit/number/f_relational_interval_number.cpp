//
// Created by zou on 3/8/24.
//
#include <boost/test/tools/old/interface.hpp>
#define BOOST_TEST_MODULE test_f_relational_interval_number
#define BOOST_TEST_DYN_LINK
#include <boost/mpl/list.hpp>
#include <boost/test/unit_test.hpp>
#include <ikos/core/number/bound.hpp>
#include <ikos/core/number/f_relational_interval_number.hpp>

using FNumber = ikos::core::FNumber;
using FBound = ikos::core::Bound< FNumber >;
using ikos::core::Signed;
using ikos::core::Unsigned;
using FRINumber = ikos::core::FRINumber;


BOOST_AUTO_TEST_CASE(test_f_abstract_constructor) {
  float x = 1.2f;
  double y = 1.2;
  std::cout.precision(30);
  std::cout<<x<<std::endl;
  std::cout<<y<<std::endl;
  std::cout <<"这是test-relation-interval-number"<< std::endl;

  FRINumber fi1(x, FRINumber::AbstractTag{});
  FRINumber fi2(y, FRINumber::AbstractTag{});
  std::cout<<"fi1: "<<fi1<<std::endl;
  std::cout<<"fi2: "<<fi2<<std::endl;

  FNumber f1(x);
  FNumber f2(y);
  std::cout.precision(30);
  std::cout<<"f1: "<<f1.value<float>()<<std::endl;
  std::cout<<"f2: "<<f2.value<double>()<<std::endl;

  //  std::cout<<"f1.bitwidth: "<<f1.bit_width()<<std::endl;
  //  std::cout<<"f2.bitwidth: "<<f2.bit_width()<<std::endl;

  FRINumber fi3(f1, FRINumber::AbstractTag{});
  FRINumber fi4(f2,FRINumber::AbstractTag{});
  std::cout<<"fi3: "<<fi3<<std::endl;
  std::cout<<"fi4: "<<fi4<<std::endl;

  FBound fb1(x);
  FBound fb2(y);
  std::cout<<"fb1: "<<fb1.number()->value<float>()<<std::endl;
  std::cout<<"fb2: "<<fb2.number()->value<double>()<<std::endl;
  //  std::cout<<"fb1.bitwidth: "<<fb1.number()->bit_width()<<std::endl;
  //  std::cout<<"fb2.bitwidth: "<<fb2.number()->bit_width()<<std::endl;

  FRINumber fi5(fb1 ,FRINumber::AbstractTag{});
  FRINumber fi6(fb2,FRINumber::AbstractTag{});
  std::cout<<"fi5: "<<fi5<<std::endl;
  std::cout<<"fi6: "<<fi6<<std::endl;
  //  BOOST_CHECK(FINumber(1.2f, FINumber::AbstractTag{}) ==
  //              FINumber(1.2f, FINumber::AbstractTag{}));

  /*  std::cout.precision(30);
    std::cout<<x<<std::endl;
    std::cout<<y<<std::endl;
    std::cout << std::endl;

    std::cout << fi1 << std::endl;
    std::cout << fi2 << std::endl;
    std::cout << std::endl;
    //  BOOST_CHECK(fi1!=fi2);
    std::cout << fi3 << std::endl;
    std::cout << fi4 << std::endl;
    std::cout << std::endl;

    std::cout << fi5 << std::endl;
    std::cout << fi6 << std::endl;*/
}
