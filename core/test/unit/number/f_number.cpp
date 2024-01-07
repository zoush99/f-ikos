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