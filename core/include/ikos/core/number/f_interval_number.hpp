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

  /// \brief Create a floating point interval number from a type
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FINumber(T lb, T ub) : _lb(lb), _ub(ub), _sign(Signed) {
    if (std::is_same< T, float >::value ||
        std::is_same< T, int >::value) { // fl
      this->_bit_width = 32;
    } else { // do
      this->_bit_width = 64;
    }
  }

  /// \brief Create a floating pointer interval number from FNumbers
  FINumber(FNumber lb, FNumber ub, uint64_t bit_width, Signedness sign)
      : _lb(lb), _ub(ub), _bit_width(bit_width), _sign(sign) {}

  /// \brief Create a floating pointer interval number from FNumbers
  FINumber(FNumber lb, FNumber ub)
      : _lb(lb), _ub(ub), _bit_width(lb.bit_width()), _sign(Signed) {}

  /// \brief Create a floating pointer interval number from FBounds
  FINumber(FBound lb, FBound ub, uint64_t bit_width, Signedness sign)
      : _lb(lb), _ub(ub), _bit_width(bit_width), _sign(sign) {}

  /// \brief Create a floating pointer interval number from Fbounds
  FINumber(FBound lb, FBound ub)
      : _lb(lb), _ub(ub), _sign(Signed) {
    if(lb.number())
  }

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

  /// \brief Return the lower bound
  const FBound& lb() const {
    ikos_assert(!this->is_bottom());
    return this->_lb;
  }

  /// \brief Return the upper bound
  const FBound& ub() const {
    ikos_assert(!this->is_bottom());
    return this->_ub;
  }

  /// \brief Return whether it is bottom
  bool is_bottom() const { return this->_lb > this->_ub; }

  /// \brief Return whether it is top
  bool is_top() const {
    return this->_lb.is_infinite() && this->_ub.is_infinite();
  }

  /// \brief Create the null floating point interval number for the given bit
  /// width
  static FINumber zero(uint64_t bit_width, Signedness sign) {
    ikos_assert_msg(bit_width > 0, "invalid bit width");

    return FINumber(0, 0, bit_width, sign);
  }

  /// @}
  /// \name Assignment Operators
  /// @{

  /// \brief Copy assignment
  FINumber& operator=(const FINumber& o) {
    if (this == &o) {
      return *this;
    }

    this->_lb = o._lb;
    this->_ub = o._ub;
    this->_sign = o._sign;
    return *this;
  }

  /// \brief Move assignment
  FINumber& operator=(FINumber&& o) noexcept {
    if (this == &o) {
      return *this;
    }

    this->_lb = o._lb;
    this->_ub = o._ub;
    this->_bit_width = o._bit_width;
    this->_sign = o._sign;
    o._bit_width = 0; // do not delete o._lb,o._ub
    return *this;
  }

  /// \brief Assignment for integral/float types
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FINumber& operator=(T n) {
    this->_lb = n;
    this->_ub = n;
    if (this->is_fl()) {
      this->_bit_width = 32;
    } else {
      this->_bit_width = 64;
    }
    this->_sign = Signed;
    return *this;
  }

  /// \brief Addition assignment
  FINumber& operator+=(const FINumber& x) {
    this->_lb += x._lb;
    this->_ub += x._ub;
    return *this;
  }

  /// \brief Subtraction assignment
  FINumber& operator-=(const FINumber& x) {
    this->_lb -= x._lb;
    this->_ub -= x._ub;
    return *this;
  }

  /// \brief Multiplication assignment
  FINumber& operator*=(const FINumber& x) {
    this->_lb *= x._lb;
    this->_ub *= x._ub;
    return *this;
  }

  /// \brief Division assignment
  FINumber& operator/=(const FINumber& x) {
    this->_lb /= x._lb;
    this->_ub /= x._ub;
    return *this;
  }

  /// @}
  /// \name Value Characterization Functions
  /// @{

  /// \brief Return the bit width of the floating point number
  uint64_t bit_width() const { return this->_bit_width; }

  /// \brief Return the signedness (Signed or Unsigned) of the floating point
  /// number Each one is a signed floating point number
  Signedness sign() const { return this->_sign; }

  bool is_signed() const { return this->_sign == Signed; }
  bool is_unsigned() const { return this->_sign == Unsigned; }

  /// @}
  /// \name Value tests
  /// @{

  /// \brief Return true if the float point interval number is [0,0]
  bool is_zero() const { return (this->_lb.is_zero() && this->_ub.is_zero()); }

  /// @}
  /// \name Conversion Functions
  /// @{

  /// \todo
  /// \brief Return a string representation of the floating point number in the
  /// given base
  /*  std::string str() const{
      return std::to_string(this->_lb.number());
    }*/

  /// @}
  /// \name Unary Operators
  /// @{

  /// \brief Set the floating point interval number to [0,0]
  void set_zero() {
    this->_lb = 0;
    this->_ub = 0;
  }

  /// \brief Unary minus
  const FINumber operator-() const {
    if (this->is_bottom()) {
      return
    } else {
      return FINumber(-this->_ub, -this->_lb);
    }
  }

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