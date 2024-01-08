//
// Created by zou on 1/7/24.
//

#pragma once

#include <ikos/core/number/compatibility.hpp>
#include <ikos/core/number/signedness.hpp>
#include <ikos/core/number/supported_integral.hpp>
#include <ikos/core/number/supported_integralorfloat.hpp>
#include <ikos/core/number/z_number.hpp>
#include <ikos/core/support/compiler.hpp>

namespace ikos {
namespace core {

/// \brief Class for floating point numbers
class FNumber {
private:
  /// If bit-width = 32, store as the float,
  /// Otherwise bit-width = 64,use double type.
  union {
    float f;  /// bit-width = 32
    double d; /// bit-width = 64
  } _n;
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
  /// \name Constructors
  /// @{

  /// \brief Default constructor
  FNumber() = delete;

  /// \brief Create a floating point number from an integral type
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FNumber(T n, uint64_t bit_width, Signedness sign)
      : _bit_width(bit_width), _sign(sign) {
    ikos_assert_msg((bit_width == 32 || bit_width == 64), "invalid bit width");

    if (this->is_fl()) {
      this->_n.f = static_cast< float >(n);
    } else {
      this->_n.d = static_cast< double >(n);
    }
  }

  /// \brief Create a floating point number from an integral type
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FNumber(T n, uint64_t bit_width, Signedness sign, NormalizedTag)
      : _bit_width(bit_width), _sign(sign) {
    ikos_assert_msg((bit_width == 32 || bit_width == 64), "invalid bit width");

    if (this->is_fl()) {
      this->_n.f = static_cast< float >(n);
    } else {
      this->_n.d = static_cast< double >(n);
    }
  }

  /// \brief Create a floating point number from a ZNumber
  FNumber(const ZNumber& n, uint64_t bit_width, Signedness sign)
      : _bit_width(bit_width), _sign(sign) {
    ikos_assert_msg((bit_width == 32 || bit_width == 64), "invalid bit width");
    if (this->is_fl()) {
      this->_n.f = n.to< int >();
    } else {
      this->_n.d = n.to< int >();
    }
  }

  /// \brief Create a floating point number from a ZNumber
  FNumber(const ZNumber& n, uint64_t bit_width, Signedness sign, NormalizedTag)
      : _bit_width(bit_width), _sign(sign) {
    ikos_assert_msg((bit_width == 32 || bit_width == 64), "invalid bit width");
    if (this->is_fl()) {
      this->_n.f = n.to< int >();
    } else {
      this->_n.d = n.to< int >();
    }
  }

public:
  /// \brief Copy constructor
  FNumber(const FNumber& o) : _bit_width(o._bit_width), _sign(o._sign) {
    if (o.is_fl()) {
      this->_n.f = o._n.f;
    } else {
      this->_n.d = o._n.d;
    }
  }

  /// \brief Move constructor
  FNumber(FNumber&& o) noexcept
      : _n(o._n), _bit_width(o._bit_width), _sign(o._sign) {
    o._bit_width = 0; // do not delete o._n.p
  }

  /// \brief Destructor
  ~FNumber() = default;

  /// \brief Create the minimum floating point number for the given bit width
  /// and sign

  /// \brief Create the maximum floating point number for the given bit width
  /// and sign

  /// \brief Create the null floating point number for the given bit width and
  /// sign
  static FNumber zero(uint64_t bit_width, Signedness sign) {
    ikos_assert_msg((bit_width == 32 || bit_width == 64), "invalid bit width");
    return FNumber(0, bit_width, sign, NormalizedTag{});
  }

  /// @}
  /// \name Assignment Operators
  /// @{

  /// \brief Copy assignment
  FNumber& operator=(const FNumber& o) {
    if (this == &o) {
      return *this;
    }

    if (this->is_fl()) {
      if (o.is_fl()) { // fl = fl
        this->_n.f = o._n.f;
      } else { // fl = do
        this->_n.f = static_cast< float >(o._n.d);
      }
    } else {
      if (o.is_fl()) { // do = fl
        this->_n.d = static_cast< double >(o._n.f);
      } else { // do = do
        this->_n.d = o._n.d;
      }
    }

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
    if (this->is_fl()) {
      this->_n.f = static_cast< float >(n);
    } else {
      this->_n.d = static_cast< double >(n);
    }
    return *this;
  }

  /// \brief Addition assignment
  FNumber& operator+=(const FNumber& x) {
    if (this->is_fl()) {
      if (x.is_fl()) { // fl += fl
        this->_n.f += x._n.f;
      } else { // fl += do
        this->_n.f += static_cast< float >(x._n.d);
      }
    } else {
      if (x.is_fl()) { // do += fl
        this->_n.d += static_cast< double >(x._n.f);
      } else { // do += do
        this->_n.d += x._n.d;
      }
    }
    return *this;
  }

  /// \brief Subtraction assignment
  FNumber& operator-=(const FNumber& x) {
    if (this->is_fl()) {
      if (x.is_fl()) { // fl -= fl
        this->_n.f -= x._n.f;
      } else { // fl -= do
        this->_n.f -= static_cast< float >(x._n.d);
      }
    } else {
      if (x.is_fl()) { // do -= fl
        this->_n.d -= static_cast< double >(x._n.f);
      } else { // do -= do
        this->_n.d -= x._n.d;
      }
    }
    return *this;
  }

  /// \brief Multiplication assignment
  FNumber& operator*=(const FNumber& x) {
    if (this->is_fl()) {
      if (x.is_fl()) { // fl *= fl
        this->_n.f *= x._n.f;
      } else { // fl *= do
        this->_n.f *= static_cast< float >(x._n.d);
      }
    } else {
      if (x.is_fl()) { // do *= fl
        this->_n.d *= static_cast< double >(x._n.f);
      } else { // do *= do
        this->_n.d *= x._n.d;
      }
    }
    return *this;
  }

  /// \brief Division assignment
  /// \todo
  FNumber& operator/=(const FNumber& x) { return *this; }

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

  /// \brief Return true if this is the minimum machine integer

  /// \brief Return true if this is the maximum machine integer

  /// \brief Return true if the machine integer is 0
  bool is_zero() const {
    if (this->is_fl()) {
      return this->_n.f == 0;
    } else {
      return this->_n.d == 0;
    }
  }

  /// @}
  /// \name Conversion Functions
  /// @{

  /// \brief Return the floating point number as a ZNumber

  /// \brief Return a string representation of the floating point number in the
  /// given base
  std::string str(int base = 10) const {
    if (this->is_fl()) {
      return std::to_string(this->_n.f);
    } else {
      return std::to_string(this->_n.d);
    }
  }

  /// @}
  /// \name Unary Operators
  /// @{

  /// \brief Set the floating point number to the minimum floating point number

  /// \brief Set the floating point number to the maximum floating point number

  /// \brief Set the floating point number to zero
  void set_zero() {
    if (this->is_fl()) {
      this->_n.f = 0;
    } else {
      this->_n.d = 0;
    }
  }

  /// \brief Unary plus

  /// \brief Prefix increment

  /// \brief Postfix increment

  /// \brief Unary minus
  const FNumber operator-() const {
    if (this->is_fl()) {
      return FNumber(-this->_n.f, this->_bit_width, this->_sign);
    } else {
      return FNumber(-this->_n.d, this->_bit_width, this->_sign);
    }
  }

  /// \brief Truncate the floating point number to the given bit width
  /// \todo
  FNumber trunc(uint64_t bit_width) const { // 32/64 -> 32/64
    ikos_assert(this->_bit_width > bit_width);

    if (this->is_fl()) { // 32 -> 32
      return FNumber(this->_n.f, bit_width, this->_sign);
    } else {
      if (bit_width == 32) { // 64 -> 32
        return FNumber(static_cast< float >(this->_n.d),
                       bit_width,
                       this->_sign);
      } else { // 64 -> 64
        return FNumber(this->_n.d, bit_width, this->_sign);
      }
    }
  }

  /// \brief Extend the floating point number to the given bit width
  /// \todo
  FNumber ext(uint64_t bit_width) const { // 32/64 -> 32/64
    ikos_assert(this->_bit_width < bit_width);

    if (this->is_fl()) {
      if (bit_width == 32) { // 32 -> 32
        return FNumber(this->_n.f, bit_width, this->_sign);
      } else { // 32 -> 64
        return FNumber(static_cast< double >(this->_n.f),
                       bit_width,
                       this->_sign);
      }
    } else { // 64 -> 64
      return FNumber(this->_n.d, bit_width, this->_sign);
    }
  }

  /// \brief Cast the floating point number to the given bit width and sign
  ///
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
      return FNumber(lhs._n.f + rhs._n.f, lhs._bit_width, lhs._sign);
    } else { // fl + do
      return FNumber(static_cast< double >(lhs._n.f) + rhs._n.d,
                     rhs._bit_width,
                     rhs._sign);
    }
  } else {
    if (rhs.is_fl()) { // do + fl
      return FNumber(lhs._n.d + static_cast< double >(rhs._n.f),
                     lhs._bit_width,
                     lhs._sign);
    } else { // do + do
      return FNumber(lhs._n.d + rhs._n.d, lhs._bit_width, lhs._sign);
    }
  }
}

/// \brief Addition
///
/// Returns the sum of the operands, with wrapping.
inline FNumber operator+(const FNumber& lhs, const FNumber& rhs) {
  return add(lhs, rhs);
}

// \brief Subtraction
///
/// Returns the difference of the operands, with wrapping.
inline FNumber sub(const FNumber& lhs, const FNumber& rhs) {
  if (lhs.is_fl()) {
    if (rhs.is_fl()) { // fl - fl
      return FNumber(lhs._n.f - rhs._n.f, lhs._bit_width, lhs._sign);
    } else { // fl - do
      return FNumber(static_cast< double >(lhs._n.f) - rhs._n.d,
                     rhs._bit_width,
                     rhs._sign);
    }
  } else {
    if (rhs.is_fl()) { // do - fl
      return FNumber(lhs._n.d - static_cast< double >(rhs._n.f),
                     lhs._bit_width,
                     lhs._sign);
    } else { // do - do
      return FNumber(lhs._n.d - rhs._n.d, lhs._bit_width, lhs._sign);
    }
  }
}

/// \brief Subtraction
///
/// Returns the difference of the operands, with wrapping.
inline FNumber operator-(const FNumber& lhs, const FNumber& rhs) {
  return sub(lhs, rhs);
}

// \brief Multiplication
///
/// Returns the product of the operands, with wrapping.
inline FNumber mul(const FNumber& lhs, const FNumber& rhs) {
  if (lhs.is_fl()) {
    if (rhs.is_fl()) { // fl * fl
      return FNumber(lhs._n.f * rhs._n.f, lhs._bit_width, lhs._sign);
    } else { // fl * do
      return FNumber(static_cast< double >(lhs._n.f) * rhs._n.d,
                     rhs._bit_width,
                     rhs._sign);
    }
  } else {
    if (rhs.is_fl()) { // do * fl
      return FNumber(lhs._n.d * static_cast< double >(rhs._n.f),
                     lhs._bit_width,
                     lhs._sign);
    } else { // do * do
      return FNumber(lhs._n.d * rhs._n.d, lhs._bit_width, lhs._sign);
    }
  }
}

/// \brief Multiplication
///
/// Returns the product of the operands, with wrapping.
inline FNumber operator*(const FNumber& lhs, const FNumber& rhs) {
  return mul(lhs, rhs);
}

// \brief Division
///
/// Returns the quotient of the operands, with wrapping.
inline FNumber div(const FNumber& lhs, const FNumber& rhs) {
  ikos_assert_msg(!rhs.is_zero(), "division by zero");
  if (lhs.is_fl()) {
    if (rhs.is_fl()) { // fl / fl
      return FNumber(lhs._n.f / rhs._n.f, lhs._bit_width, lhs._sign);
    } else { // fl / do
      return FNumber(static_cast< double >(lhs._n.f) / rhs._n.d,
                     rhs._bit_width,
                     rhs._sign);
    }
  } else {
    if (rhs.is_fl()) { // do / fl
      return FNumber(lhs._n.d / static_cast< double >(rhs._n.f),
                     lhs._bit_width,
                     lhs._sign);
    } else { // do / do
      return FNumber(lhs._n.d / rhs._n.d, lhs._bit_width, lhs._sign);
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
  if (lhs.is_fl()) {
    if (rhs.is_fl()) { // fl == fl
      return lhs._n.f == rhs._n.f;
    } else { // fl == do
      return static_cast< double >(lhs._n.f) == rhs._n.d;
    }
  } else {
    if (rhs.is_fl()) { // do == fl
      return lhs._n.d == static_cast< double >(rhs._n.f);
    } else { // do == do
      return lhs._n.d == rhs._n.d;
    }
  }
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
  if (lhs.is_fl()) {
    if (rhs.is_fl()) { // fl != fl
      return lhs._n.f != rhs._n.f;
    } else { // fl != do
      return static_cast< double >(lhs._n.f) != rhs._n.d;
    }
  } else {
    if (rhs.is_fl()) { // do != fl
      return lhs._n.d != static_cast< double >(rhs._n.f);
    } else { // do != do
      return lhs._n.d != rhs._n.d;
    }
  }
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
  if (lhs.is_fl()) {
    if (rhs.is_fl()) { // fl < fl
      return lhs._n.f < rhs._n.f;
    } else { // fl < do
      return static_cast< double >(lhs._n.f) < rhs._n.d;
    }
  } else {
    if (rhs.is_fl()) { // do < fl
      return lhs._n.d < static_cast< double >(rhs._n.f);
    } else { // do < do
      return lhs._n.d < rhs._n.d;
    }
  }
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
  if (lhs.is_fl()) {
    if (rhs.is_fl()) { // fl <= fl
      return lhs._n.f <= rhs._n.f;
    } else { // fl <= do
      return static_cast< double >(lhs._n.f) <= rhs._n.d;
    }
  } else {
    if (rhs.is_fl()) { // do <= fl
      return lhs._n.d <= static_cast< double >(rhs._n.f);
    } else { // do <= do
      return lhs._n.d <= rhs._n.d;
    }
  }
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
  if (lhs.is_fl()) {
    if (rhs.is_fl()) { // fl > fl
      return lhs._n.f > rhs._n.f;
    } else { // fl > do
      return static_cast< double >(lhs._n.f) > rhs._n.d;
    }
  } else {
    if (rhs.is_fl()) { // do > fl
      return lhs._n.d > static_cast< double >(rhs._n.f);
    } else { // do > do
      return lhs._n.d > rhs._n.d;
    }
  }
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
  if (lhs.is_fl()) {
    if (rhs.is_fl()) { // fl >= fl
      return lhs._n.f >= rhs._n.f;
    } else { // fl >= do
      return static_cast< double >(lhs._n.f) >= rhs._n.d;
    }
  } else {
    if (rhs.is_fl()) { // do >= fl
      return lhs._n.d >= static_cast< double >(rhs._n.f);
    } else { // do >= do
      return lhs._n.d >= rhs._n.d;
    }
  }
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

/// \brief Return the greater of the given floating point numbers
inline const FNumber& max(const FNumber& a, const FNumber& b) {
  return (a < b) ? b : a;
}

/// \brief Return the absolute value of the given floating point numbers
inline FNumber abs(const FNumber& n) {
  return n < 0 ? -n : n;
}

/// @}
/// \name Input / Output
/// @{

/// \brief Write a machine integer on a stream
inline std::ostream& operator<<(std::ostream& o, const FNumber& n) {
  if (n.is_fl()) {
      o << n._n.f;
  } else {
    o << n._n.d;
  }
  return o;
}

/// @}

/// \brief Return the hash of a MachineInt
inline std::size_t hash_value(const FNumber& n) {
  std::size_t hash = 0;
  if (n.is_fl()) {
    boost::hash_combine(hash, n._n.f);
  } else {
    boost::hash_combine(hash, n._n.d);
  }
  boost::hash_combine(hash, n._bit_width);
  boost::hash_combine(hash, n._sign);
  return hash;
}

} // end namespace core
} // end namespace ikos


namespace std {

/// \brief Hash for MachineInt
template <>
struct hash< ikos::core::FNumber > {
  std::size_t operator()(const ikos::core::FNumber& n) const {
    return ikos::core::hash_value(n);
  }
};

} // end namespace std
