//
// Created by zou on 1/7/24.
//


#pragma once

#include <type_traits>

namespace ikos {
namespace core {

/// \brief Checks whether T is a supported integral type.
///
/// Supported integral types are:
///   * int, unsigned int
///   * long, unsigned long
///   * long long, unsigned long long
///   * float, double
template < typename T >
struct IsSupportedIntegralOrFloat : public std::false_type {};

template <>
struct IsSupportedIntegralOrFloat< int > : public std::true_type {};

template <>
struct IsSupportedIntegralOrFloat< unsigned int > : public std::true_type {};

template <>
struct IsSupportedIntegralOrFloat< long > : public std::true_type {};

template <>
struct IsSupportedIntegralOrFloat< unsigned long > : public std::true_type {};

template <>
struct IsSupportedIntegralOrFloat< long long > : public std::true_type {};

template <>
struct IsSupportedIntegralOrFloat< unsigned long long > : public std::true_type {};

template <>
struct IsSupportedIntegralOrFloat< float > : public std::true_type {};

template <>
struct IsSupportedIntegralOrFloat< double > : public std::true_type {};

} // end namespace core
} // end namespace ikos
