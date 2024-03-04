//
// Created by zou on 3/4/24.
//

#pragma once

#include <ikos/core/number/bound.hpp> // By zoush99
#include <ikos/core/number/compatibility.hpp>
#include <ikos/core/number/signedness.hpp>
#include <ikos/core/number/supported_integralorfloat.hpp>
#include <ikos/core/support/compiler.hpp>
// #include <ikos/core/value/numeric/interval.hpp> // By zoush99

namespace ikos {
namespace core {

/// \brief Class for floating point interval numbers
class FINumber {
private:
  ///
  FBound _lb; /// [_lb,_ub]: [FNumber,FNumber]
  FBound _ub;
  uint64_t _bit_width;
  Signedness _sign;

private:
  /// \brief Return true if bit-width = 32
  bool is_fl() const { return ikos_likely(this->_bit_width == 32); }

  /// \brief Return true if bit-width = 64
  bool is_do() const { return ikos_likely(this->_bit_width == 64); }

public:
  /// \name Constructors
  /// @{

  /// \brief Default
  FINumber() : _lb(1), _ub(1), _bit_width(32), _sign(Signed) {}

  /// \brief Create a floating point interval number from a type
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FINumber(T lb, T ub, uint64_t bit_width, Signedness sign)
      : _lb(lb), _ub(ub), _bit_width(bit_width), _sign(sign) {}

  /// \brief Create a floating pointer interval number from FNumbers
  FINumber(FNumber lb, FNumber ub, uint64_t bit_width, Signedness sign)
      : _lb(lb), _ub(ub), _bit_width(bit_width), _sign(sign) {}

public:
  /// \brief Copy constructor
  FINumber(const FINumber& o)
      : _lb(o._lb), _ub(o._ub), _bit_width(o._bit_width), _sign(o._sign) {}

  /// \brief Move constructor
  FINumber(FINumber&& o) noexcept
      : _lb(o._lb), _ub(o._ub), _bit_width(o._bit_width), _sign(o._sign) {
    o._bit_width = 0; // do not delete o
  }

  /// \brief Destructor
  ~FINumber() = default;

public:
  // friends

  friend bool operator==(const FINumber& lhs, const FINumber& rhs);
};
// end class FINumber

/// \brief Equality operator
inline bool operator==(const FINumber& lhs, const FINumber& rhs) {
  return (lhs._lb == rhs._lb && lhs._ub == rhs._ub);
}
} // end namespace core
} // end namespace ikos