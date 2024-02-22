//
// Created by zou on 2/20/24.
//

#pragma once

#include <llvm/ADT/APFloat.h> // By zoush99
#include <ikos/core/number/compatibility.hpp>
#include <ikos/core/number/signedness.hpp>
#include <ikos/core/number/supported_integralorfloat.hpp>
#include <ikos/core/number/z_number.hpp>
#include <ikos/core/support/compiler.hpp>

namespace ikos {
namespace core {

/// \brief Class for floating point numbers
class FNumber {
private:
  /// llvm::APFloat class
  llvm::APFloat _n;
  uint64_t _bit_width;
  Signedness _sign;

private:
  /// \brief Return true if bit-width = 32
  bool is_fl() const { return ikos_likely(this->_bit_width == 32); }

  /// \brief Return true if bit-width = 64
  bool is_do() const { return ikos_likely(this->_bit_width == 64); }

  /// \brief To harmonize with machine integer types
  struct NormalizedTag {};

public:
  /// \name Construtors
  /// @{

  /// \brief Default constructor
  FNumber() : _n(1.0), _bit_width(64), _sign(Signedness::Signed) {}

  /// \brief Create a floating point number from a type
  FNumber(int n, uint64_t bit_width, Signedness sign)
      : _n(static_cast< double >(n)), _bit_width(bit_width), _sign(sign) {}

  /// \brief Create a floating point number from a type
  FNumber(float n, uint64_t bit_width, Signedness sign)
      : _n(n), _bit_width(bit_width), _sign(sign) {}

  /// \brief Create a floating point number from a type
  FNumber(double n, uint64_t bit_width, Signedness sign)
      : _n(n), _bit_width(bit_width), _sign(sign) {}

  /// \brief Create a floating point number from a type
  FNumber(int n)
      : _n(static_cast< double >(n)), _bit_width(64), _sign(Signedness::Signed) {}

  /// \brief Create a floating point number from a type
  FNumber(float n)
      : _n(n), _bit_width(32), _sign(Signedness::Signed) {}

  /// \brief Create a floating point number from a type
  FNumber(double n)
      : _n(n), _bit_width(64), _sign(Signedness::Signed) {}

  /*  /// \brief Create a floating point number from a ZNumber
    FNumber(const ZNumber& n, uint64_t bit_width, Signedness sign)
        : _bit_width(bit_width), _sign(sign) {
      ikos_assert_msg((bit_width == 32 || bit_width == 64), "invalid bit
    width"); this->_n = llvm::APFloat(static_cast< float >(n.to< int >()));
    }

    /// \brief Create a floating point number from a ZNumber
    FNumber(const ZNumber& n, uint64_t bit_width, Signedness sign,
    NormalizedTag) : _bit_width(bit_width), _sign(sign) {
      ikos_assert_msg((bit_width == 32 || bit_width == 64), "invalid bit
    width"); this->_n = llvm::APFloat(static_cast< float >(n.to< int >()));
    }*/

  /// \brief Create a floating point number from a llvm::APFloat class
  FNumber(llvm::APFloat& n, uint64_t bit_width)
      : _n(n), _bit_width(bit_width), _sign(Signedness::Signed) {}

public:
  /// \brief Copy constructor
  FNumber(const FNumber& o)
      : _n(o._n), _bit_width(o._bit_width), _sign(o._sign) {}

  /// \brief Move constructor
  FNumber(FNumber&& o) noexcept
      : _n(o._n), _bit_width(o._bit_width), _sign(o._sign) {
    o._bit_width = 0; // do not delete o._n.p
  }

  /// \brief Destructor
  ~FNumber() = default;

  /// \brief It is aimed at normalized numbers and does not consider
  /// denormalized numbers. \brief Create the minimum machine integer for the
  /// given bit width and sign
  static FNumber min(uint64_t bit_width, Signedness sign) {
    ikos_assert_msg(bit_width > 0, "invalid bit width");
    // By default, all are signed.
    if (bit_width == 32) { // fl
      return FNumber(-3.4028235E38f, 32, sign);
    } else { // do
      return FNumber(-1.7976931348623157E308, 64, sign);
    }
  }

  /// \brief Create the maximum machine integer for the given bit width and sign
  static FNumber max(uint64_t bit_width, Signedness sign) {
    ikos_assert_msg(bit_width > 0, "invalid bit width");
    // By default, all are signed.
    if (bit_width == 32) { // fl
      return FNumber(3.4028235E38f, 32, sign);
    } else { // do
      return FNumber(1.7976931348623157E308, 64, sign);
    }
  }

  /// \brief Create the null floating point number for the given bit width and
  /// sign
  static FNumber zero(uint64_t bit_width, Signedness sign) {
    ikos_assert_msg((bit_width == 32 || bit_width == 64), "invalid bit width");
    return FNumber(0, bit_width, sign);
  }

  /// @}
  /// \name Assignment Operators
  /// @{

  /// \brief Copy assignment
  FNumber& operator=(const FNumber& o) {
    if (this == &o) {
      return *this;
    }
    this->_n = o._n;
    this->_bit_width = o._bit_width;
    this->_sign = o._sign;
    return *this;
  }

  /// \brief Move assignment
  FNumber& operator=(FNumber&& o) noexcept {
    if (this == &o) {
      return *this;
    }
    this->_n = o._n;
    this->_bit_width = o._bit_width;
    this->_sign = o._sign;
    o._bit_width = 0; // do not delete o._n.p
    return *this;
  }

  /// \brief Assignment for integral/float types
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FNumber& operator=(T n) {
    if (this->is_fl()) { // fl
      this->_n = llvm::APFloat(static_cast< float >(n));
    } else { // do
      this->_n = llvm::APFloat(static_cast< double >(n));
    }
    return *this;
  }

  /// \brief Addition assignment
  FNumber& operator+=(const FNumber& x) {
    this->_n = this->_n + x._n;
    return *this;
  }

  /// \brief Subtraction assignment
  FNumber& operator-=(const FNumber& x) {
    this->_n = this->_n - x._n;
    return *this;
  }

  /// \brief Multiplication assignment
  FNumber& operator*=(const FNumber& x) {
    this->_n = this->_n * x._n;
    return *this;
  }

  /// \brief Division assignment
  FNumber& operator/=(const FNumber& x) {
    this->_n = this->_n / x._n;
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

  /// \brief It is aimed at normalized numbers and does not consider
  /// denormalized numbers. \brief Return true if this is the minimum machine
  /// integer
  bool is_min() const {
    if (this->_bit_width == 32) { // fl
      return this->_n == llvm::APFloat(-3.4028235E38f);
    } else { // do
      return this->_n == llvm::APFloat(-1.7976931348623157E308);
    }
  }

  /// \brief Return true if this is the maximum machine integer
  bool is_max() const {
    if (this->_bit_width == 32) { // fl
      return this->_n == llvm::APFloat(3.4028235E38f);
    } else { // do
      return this->_n == llvm::APFloat(1.7976931348623157E308);
    }
  }

  /// \brief Return true if the machine integer is 0
  bool is_zero() const { return this->_n.isZero(); }

  /// @}
  /// \name Unary Operators
  /// @{

  /// \brief Set the floating point number to zero
  void set_zero() { this->_n == llvm::APFloat(0.0f); }

  /// \brief Unary minus
  const FNumber operator-() const {
    llvm::APFloat nega = -this->_n; // take the negative
    return FNumber(nega, this->_bit_width);
  }

  /// \todo
  /// \brief Truncate the floating point number to the given bit width

  /// \brief Extend the floating point number to the given bit width

  /// \brief Cast the floating point number to the given bit width and sign

  /// This is equivalent to trunc()/ext() + sign_cast() (in this specific order)

  /// @}

private:
  // Helpers for binary operations

  /// \brief Check if an overflow occurred

  /// \brief Check if an underflow occurred

public:
  // friends

  friend FNumber add(const FNumber& lhs, const FNumber& rhs);

  friend FNumber operator+(const FNumber& lhs, const FNumber& rhs);

  friend FNumber sub(const FNumber& lhs, const FNumber& rhs);

  friend FNumber operator-(const FNumber& lhs, const FNumber& rhs);

  friend FNumber mul(const FNumber& lhs, const FNumber& rhs);

  friend FNumber operator*(const FNumber& lhs, const FNumber& rhs);

  friend FNumber div(const FNumber& lhs, const FNumber& rhs);

  friend FNumber operator/(const FNumber& lhs, const FNumber& rhs);

  friend bool operator==(const FNumber& lhs, const FNumber& rhs);

  friend bool operator!=(const FNumber& lhs, const FNumber& rhs);

  friend bool operator<(const FNumber& lhs, const FNumber& rhs);

  friend bool operator<=(const FNumber& lhs, const FNumber& rhs);

  friend bool operator>(const FNumber& lhs, const FNumber& rhs);

  friend bool operator>=(const FNumber& lhs, const FNumber& rhs);

  friend std::ostream& operator<<(std::ostream& o, const FNumber& n);

  friend std::size_t hash_value(const FNumber&);

}; // end class FNumber

/// \name Binary Operators
/// @{

/// \brief Addition
///
/// Returns the sum of the operands, with wrapping.
inline FNumber add(const FNumber& lhs, const FNumber& rhs) {
  if (lhs.is_fl()) {
    if (rhs.is_fl()) { // fl + fl
      return FNumber(lhs._n.convertToFloat() + rhs._n.convertToFloat(),
                     lhs._bit_width,
                     lhs._sign);
    } else { // fl + do
      return FNumber(lhs._n.convertToDouble() + rhs._n.convertToDouble(),
                     rhs._bit_width,
                     rhs._sign);
    }
  } else {
    if (rhs.is_fl()) { // do + fl
      return FNumber(lhs._n.convertToDouble() + rhs._n.convertToDouble(),
                     lhs._bit_width,
                     lhs._sign);
    } else { // do + do
      return FNumber(lhs._n.convertToDouble() + rhs._n.convertToDouble(),
                     lhs._bit_width,
                     lhs._sign);
    }
  }
}

/// \brief Addition
///
/// Returns the sum of the operands, with wrapping.
inline FNumber operator+(const FNumber& lhs, const FNumber& rhs) {
  return add(lhs, rhs);
}

/// \brief Subtraction
///
/// Returns the difference of the operands, with wrapping.
inline FNumber sub(const FNumber& lhs, const FNumber& rhs) {
  if (lhs.is_fl()) {
    if (rhs.is_fl()) { // fl - fl
      return FNumber(lhs._n.convertToFloat() - rhs._n.convertToFloat(),
                     lhs._bit_width,
                     lhs._sign);
    } else { // fl - do
      return FNumber(lhs._n.convertToDouble() - rhs._n.convertToDouble(),
                     rhs._bit_width,
                     rhs._sign);
    }
  } else {
    if (rhs.is_fl()) { // do - fl
      return FNumber(lhs._n.convertToDouble() - rhs._n.convertToDouble(),
                     lhs._bit_width,
                     lhs._sign);
    } else { // do - do
      return FNumber(lhs._n.convertToDouble() - rhs._n.convertToDouble(),
                     lhs._bit_width,
                     lhs._sign);
    }
  }
}

/// \brief Subtraction
///
/// Returns the difference of the operands, with wrapping.
inline FNumber operator-(const FNumber& lhs, const FNumber& rhs) {
  return sub(lhs, rhs);
}

/// \brief Multiplication
///
/// Returns the product of the operands, with wrapping.
inline FNumber mul(const FNumber& lhs, const FNumber& rhs) {
  if (lhs.is_fl()) {
    if (rhs.is_fl()) { // fl * fl
      return FNumber(lhs._n.convertToFloat() * rhs._n.convertToFloat(),
                     lhs._bit_width,
                     lhs._sign);
    } else { // fl * do
      return FNumber(lhs._n.convertToDouble() * rhs._n.convertToDouble(),
                     rhs._bit_width,
                     rhs._sign);
    }
  } else {
    if (rhs.is_fl()) { // do * fl
      return FNumber(lhs._n.convertToDouble() * rhs._n.convertToDouble(),
                     lhs._bit_width,
                     lhs._sign);
    } else { // do * do
      return FNumber(lhs._n.convertToDouble() * rhs._n.convertToDouble(),
                     lhs._bit_width,
                     lhs._sign);
    }
  }
}

/// \brief Multiplication
///
/// Returns the product of the operands, with wrapping.
inline FNumber operator*(const FNumber& lhs, const FNumber& rhs) {
  return mul(lhs, rhs);
}

/// \brief Division
///
/// Returns the quotient of the operands, with wrapping.
inline FNumber div(const FNumber& lhs, const FNumber& rhs) {
  ikos_assert_msg(!rhs.is_zero(), "division by zero");
  if (lhs.is_fl()) {
    if (rhs.is_fl()) { // fl / fl
      return FNumber(lhs._n.convertToFloat() / rhs._n.convertToFloat(),
                     lhs._bit_width,
                     lhs._sign);
    } else { // fl / do
      return FNumber(lhs._n.convertToDouble() / rhs._n.convertToDouble(),
                     rhs._bit_width,
                     rhs._sign);
    }
  } else {
    if (rhs.is_fl()) { // do / fl
      return FNumber(lhs._n.convertToDouble() / rhs._n.convertToDouble(),
                     lhs._bit_width,
                     lhs._sign);
    } else { // do / do
      return FNumber(lhs._n.convertToDouble() / rhs._n.convertToDouble(),
                     lhs._bit_width,
                     lhs._sign);
    }
  }
}

/// \brief Division
///
/// Returns the quotient of the operands, with wrapping.
inline FNumber operator/(const FNumber& lhs, const FNumber& rhs) {
  return div(lhs, rhs);
}

/// @}
/// \name Comparison Operators
/// @{

/// \brief Equality operator
inline bool operator==(const FNumber& lhs, const FNumber& rhs) {
  return lhs._n == rhs._n;
}

/// \brief Equality operator with floating point number types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
inline bool operator==(const FNumber& lhs, T rhs) {
  return lhs == FNumber(rhs, lhs.bit_width(), lhs.sign());
}

/// \brief Equality operator with floating point number types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
inline bool operator==(T lhs, const FNumber& rhs) {
  return FNumber(lhs, rhs.bit_width(), rhs.sign()) == rhs;
}

/// \brief Inequality operator
inline bool operator!=(const FNumber& lhs, const FNumber& rhs) {
  return lhs._n != rhs._n;
}

/// \brief Inequality operator with floating point number types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
inline bool operator!=(const FNumber& lhs, T rhs) {
  return lhs != FNumber(rhs, lhs.bit_width(), lhs.sign());
}

/// \brief Inequality operator with floating point number types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
inline bool operator!=(T lhs, const FNumber& rhs) {
  return FNumber(lhs, rhs.bit_width(), rhs.sign()) != rhs;
}

/// \brief Less than comparison
inline bool operator<(const FNumber& lhs, const FNumber& rhs) {
  return lhs._n < rhs._n;
}

/// \brief Less than comparison with floating point number types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
inline bool operator<(const FNumber& lhs, T rhs) {
  return lhs < FNumber(rhs, lhs.bit_width(), lhs.sign());
}

/// \brief Less than comparison with floating point number types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
inline bool operator<(T lhs, const FNumber& rhs) {
  return FNumber(lhs, rhs.bit_width(), rhs.sign()) < rhs;
}

/// \brief Less or equal than comparison
inline bool operator<=(const FNumber& lhs, const FNumber& rhs) {
  return lhs._n <= rhs._n;
}

/// \brief Less or equal comparison with floating point number types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
inline bool operator<=(const FNumber& lhs, T rhs) {
  return lhs <= FNumber(rhs, lhs.bit_width(), lhs.sign());
}

/// \brief Less or equal comparison with floating point number types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
inline bool operator<=(T lhs, const FNumber& rhs) {
  return FNumber(lhs, rhs.bit_width(), rhs.sign()) <= rhs;
}

/// \brief Greater than comparison
inline bool operator>(const FNumber& lhs, const FNumber& rhs) {
  return lhs._n > rhs._n;
}

/// \brief Greater than comparison with floating point number types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
inline bool operator>(const FNumber& lhs, T rhs) {
  return lhs > FNumber(rhs, lhs.bit_width(), lhs.sign());
}

/// \brief Greater than comparison with floating point number types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
inline bool operator>(T lhs, const FNumber& rhs) {
  return FNumber(lhs, rhs.bit_width(), rhs.sign()) > rhs;
}

/// \brief Greater or equal comparison
inline bool operator>=(const FNumber& lhs, const FNumber& rhs) {
  return lhs._n >= rhs._n;
}

/// \brief Greater or equal comparison with floating point number types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
inline bool operator>=(const FNumber& lhs, T rhs) {
  return lhs >= FNumber(rhs, lhs.bit_width(), lhs.sign());
}

/// \brief Greater or equal comparison with floating point number types
template < typename T,
           class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
inline bool operator>=(T lhs, const FNumber& rhs) {
  return FNumber(lhs, rhs.bit_width(), rhs.sign()) >= rhs;
}

/// @}
/// \name Utility functions (min, max, etc.)
/// @{

/// \brief Return the smaller of the given floating point numbers
inline const FNumber& min(const FNumber& a, const FNumber& b) {
  return (a < b) ? a : b;
}

/// \brief Return the smaller of the given numbers
inline const FNumber& min(const FNumber& a,
                          const FNumber& b,
                          const FNumber& c) {
  return min(min(a, b), c);
}

/// \brief Return the smaller of the given numbers
inline const FNumber& min(const FNumber& a,
                          const FNumber& b,
                          const FNumber& c,
                          const FNumber& d) {
  return min(min(min(a, b), c), d);
}

/// \brief Return the greater of the given floating point numbers
inline const FNumber& max(const FNumber& a, const FNumber& b) {
  return (a < b) ? b : a;
}

/// \brief Return the greater of the given numbers
inline const FNumber& max(const FNumber& a,
                          const FNumber& b,
                          const FNumber& c) {
  return max(max(a, b), c);
}

/// \brief Return the greater of the given numbers
inline const FNumber& max(const FNumber& a,
                          const FNumber& b,
                          const FNumber& c,
                          const FNumber& d) {
  return max(max(max(a, b), c), d);
}

/// \brief Return the absolute value of the given floating point numbers
inline FNumber abs(const FNumber& n) {
  return n < 0 ? -n : n;
}

/// @}
/// \name Input / Output
/// @{

/// \brief Write a floating point number on a stream
inline std::ostream& operator<<(std::ostream& o, const FNumber& n) {
  if (n.is_fl()) {
    o << n._n.convertToFloat();
  } else {
    o << n._n.convertToDouble();
  }
  return o;
}

/// @}

/// \brief Return the hash of a MachineInt
inline std::size_t hash_value(const FNumber& n) {
  std::size_t hash = 0;
  if (n.is_fl()) {
    boost::hash_combine(hash, n._n.convertToFloat());
  } else {
    boost::hash_combine(hash, n._n.convertToDouble());
  }
  boost::hash_combine(hash, n._bit_width);
  boost::hash_combine(hash, n._sign);
  return hash;
}

} // namespace core
} // namespace ikos