//
// Created by zou on 3/4/24.
//

#pragma once

#include <ikos/core/number/bound.hpp> // By zoush99
#include <ikos/core/number/signedness.hpp>
#include <ikos/core/number/supported_integralorfloat.hpp>
#include <iostream>

namespace ikos {
namespace core {

namespace detail {
/// \brief Covert floating point numbers to binary representation
template < typename T >
void decompose_fl(T _value,
                     int& sign_bit,
                     int& exponent,
                     long long& mantissa) {
  if (std::is_same< T, float >::value) { // fl
    int _bits = *reinterpret_cast< int* >(&_value);

    sign_bit = _bits >> 31 & 1;
    exponent = _bits >> 23 & 0xFF;
    mantissa = _bits & 0x7FFFFF;
  } else { // do
    long long _bits = *reinterpret_cast< long long* >(&_value);

    sign_bit = _bits >> 63 & 1;
    exponent = _bits >> 52 & 0x7FF;
    mantissa = _bits & 0xFFFFFFFFFFFFFLL;
  }
}

/// \brief Convert binary representations to floating point numbers
template < typename T >
T compose_fl(int sign_bit, int exponent, long long mantissa) {
  if (std::is_same< T, float >::value) { // fl
    int _bits = (sign_bit << 31) | (exponent << 23) | mantissa;

    T result = *reinterpret_cast< float* >(&_bits);
    return result;
  } else { // do
    long long _bits = (static_cast< long long >(sign_bit) << 63) |
                            (static_cast< long long >(exponent) << 52) |
                            mantissa;

    T result = *reinterpret_cast< double* >(&_bits);
    return result;
  }
}

/// \brief Find the nearest floating point number that is less than the nearest
/// neighbor
template < typename T >
T find_next_value_down(T _value) {
  int sign_bit, exponent;
  long long mantissa;
  decompose_fl< T >(_value, sign_bit, exponent, mantissa);

  if (exponent == 0 && mantissa == 0) { // Non-normalized number
    mantissa -= 1;
  } else {
    if (mantissa == 0) {                     // Sub-normal number
      if (std::is_same< T, float >::value) { // fl
        mantissa = (1LL << 23) - 1;
      } else { // do
        mantissa = (1LL << 52) - 1;
      }
      exponent -= 1;
    } else { // Normalized number
      mantissa -= 1;
    }
  }

  return compose_fl< T >(sign_bit, exponent, mantissa);
}

/// \brief Find the nearest floating point number that is greater than the
/// nearest neighbor
template < typename T >
T find_next_value_up(T _value) {
  int sign_bit, exponent;
  long long mantissa;
  decompose_fl< T >(_value, sign_bit, exponent, mantissa);

  if (exponent == 0 && mantissa == 0) { // Non-normalized number
    mantissa += 1;
  } else {
    if (std::is_same< T, float >::value &&
        mantissa == (1LL << 23) - 1) { // fl // Sub-normal number
      mantissa = 0;
      exponent += 1;
    } else if (std::is_same< T, double >::value &&
               mantissa == (1LL << 52) - 1) { // do // Sub-normal number
      mantissa = 0;
      exponent += 1;
    } else { // Normalized number
      mantissa += 1;
    }
  }

  return compose_fl< T >(sign_bit, exponent, mantissa);
}

} // namespace detail

/// \brief Class for floating point interval numbers
class FINumber {
private:
  FBound _lb; /// [_lb,_ub]: [FNumber,FNumber]
  FBound _ub;
  uint64_t _bit_width;
  Signedness _sign;

private:
  struct TopTag {};
  struct BottomTag {};

  /// \brief Create the top floating point interval number [-oo, +oo]
  explicit FINumber(TopTag)
      : _lb(FBound ::minus_infinity()), _ub(FBound ::plus_infinity()) {}

  /// \brief Create the bottom floating point interval number
  explicit FINumber(BottomTag) : _lb(1), _ub(0) {}

public:
  /// \brief Label that require abstraction
  struct AbstractTag {};

private:
  /// \brief Return true if bit-width = 32
  bool is_fl() const { return ikos_likely(this->_bit_width == 32); }

  /// \brief Return true if bit-width = 64
  bool is_do() const { return ikos_likely(this->_bit_width == 64); }

public:
  /// \brief Create the floating point interval number [-oo, +oo]
  static FINumber top() { return FINumber(TopTag{}); }

  /// \brief Create the bottom floating point interval number
  static FINumber bottom() { return FINumber(BottomTag{}); }

  /// \name Constructors
  /// @{

  /// \brief Default constructor
  FINumber() : _lb(1), _ub(1), _bit_width(32), _sign(Signed) {}

  /// \brief Create a floating point interval number from a type
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FINumber(T v, uint64_t bit_width, Signedness sign)
      : _lb(v), _ub(v), _bit_width(bit_width), _sign(sign) {}

  /// \brief Label that require abstraction
  /// \brief Create a floating point interval number from a type
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FINumber(T v, uint64_t bit_width, Signedness sign, AbstractTag)
      : _lb(detail::find_next_value_down(v)),
        _ub(detail::find_next_value_up(v)),
        _bit_width(bit_width),
        _sign(sign) {}

  /// \brief Create a floating point interval number from a type
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FINumber(T v) : _lb(v), _ub(v), _sign(Signed) {
    if (std::is_same< T, float >::value ||
        std::is_same< T, int >::value) { // fl
      this->_bit_width = 32;
    } else { // do
      this->_bit_width = 64;
    }
  }

  /// \brief Label that require abstraction
  /// \brief Create a floating point interval number from a type
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FINumber(T v, AbstractTag)
      : _lb(detail::find_next_value_down(v)),
        _ub(detail::find_next_value_up(v)),
        _sign(Signed) {
    if (std::is_same< T, float >::value ||
        std::is_same< T, int >::value) { // fl
      this->_bit_width = 32;
    } else { // do
      this->_bit_width = 64;
    }
  }

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

  /// \brief Create a floating pointer interval number from a FNumber
  FINumber(FNumber v) {
    if (v.bit_width() == 32) { // fl
      this->_lb = v.value< float >();
      this->_ub = v.value< float >();
    } else if (v.bit_width() == 64) { // do
      this->_lb = v.value< double >();
      this->_ub = v.value< double >();
    } else {
      this->_lb = this->_ub = 1;
    }
  }

  /// \brief Label that require abstraction
  /// \brief Create a floating pointer interval number from a FNumber
  FINumber(FNumber v, AbstractTag) {
    if (v.bit_width() == 32) { // fl
      this->_lb = std::move(FBound(detail::find_next_value_down(v.value< float >())));
      this->_ub = std::move(FBound(detail::find_next_value_up(v.value< float >())));
    } else if (v.bit_width() == 64) { // do
      this->_lb = std::move(FBound(detail::find_next_value_down(v.value< double >())));
      this->_ub = std::move(FBound(detail::find_next_value_up(v.value< double >())));
    } else {
      this->_lb = this->_ub = 1;
    }
    this->_bit_width = v.bit_width();
  }

  /// \brief Create a floating pointer interval number from FNumbers
  FINumber(FNumber lb, FNumber ub, uint64_t bit_width, Signedness sign)
      : _lb(lb), _ub(ub), _bit_width(bit_width), _sign(sign) {}

  /// \brief Create a floating pointer interval number from FNumbers
  FINumber(FNumber lb, FNumber ub)
      : _lb(lb), _ub(ub), _bit_width(lb.bit_width()), _sign(Signed) {}

  /// \brief Create a floating pointer interval number from a Fbound
  FINumber(FBound v) {
    if (v.number().is_initialized() &&
        v.number()->bit_width() == 32) { // x is not empty and fl
      this->_lb = v.number()->value< float >();
      this->_ub = v.number()->value< float >();
    } else if (v.number().is_initialized() &&
               v.number()->bit_width() == 64) { // do
      this->_lb = v.number()->value< double >();
      this->_ub = v.number()->value< double >();
    } else { // none
      this->_lb = this->_ub = 1;
    }
    this->_bit_width = v.number()->bit_width();
  }

  /// \brief Label that require abstraction
  /// \brief Create a floating pointer interval number from a Fbound
  FINumber(FBound v, AbstractTag) {
    if (v.number().is_initialized() &&
        v.number()->bit_width() == 32) { // x is not empty and fl
      this->_lb =
          std::move(FBound(detail::find_next_value_down(v.number()->value< float >())));
      this->_ub =
          std::move(FBound(detail::find_next_value_up(v.number()->value< float >())));
    } else if (v.number().is_initialized() &&
               v.number()->bit_width() == 64) { // x is not empty and do
      this->_lb =
          std::move(FBound(detail::find_next_value_down(v.number()->value< double >())));
      this->_ub =
          std::move(FBound(detail::find_next_value_up(v.number()->value< double >())));
    } else { // none
      this->_lb = this->_ub = 1;
    }
  }

  /// \brief Create a floating pointer interval number from FBounds
  FINumber(FBound lb, FBound ub, uint64_t bit_width, Signedness sign)
      : _lb(lb), _ub(ub), _bit_width(bit_width), _sign(sign) {}

  /// \brief Create a floating pointer interval number from Fbounds
  FINumber(FBound lb, FBound ub) : _lb(lb), _ub(ub), _sign(Signed) {
    if (lb.number().is_initialized() &&
        ub.number().is_initialized()) { // lb and ub are not empty
      this->_bit_width = lb.number()->bit_width();
    } else { // none
      this->_bit_width = 0;
    }
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
  const FBound& lb() const { return this->_lb; }

  /// \brief Return the upper bound
  const FBound& ub() const { return this->_ub; }

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
    o._bit_width = 0; // do not delete o._lb,o._ub
    return *this;
  }

  /// \brief Assignment for integral/float types
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FINumber& operator=(T n) {
    this->_lb = std::move(FBound (n));
    this->_ub = std::move(FBound (n));
    if (std::is_same< T, float >::value ||
        std::is_same< T, int >::value) { // fl
      this->_bit_width = 32;
    } else { // do
      this->_bit_width = 64;
    }
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
    this->_lb -= x._ub;
    this->_ub -= x._lb;
    return *this;
  }

  /// \brief Multiplication assignment
  FINumber& operator*=(const FINumber& x) {
    FBound ll = this->lb() * x.lb();
    FBound lu = this->lb() * x.ub();
    FBound ul = this->ub() * x.lb();
    FBound uu = this->ub() * x.ub();
    this->_lb = min(ll, lu, ul, uu);
    this->_ub = max(ll, lu, ul, uu);
    return *this;
  }

  /// \brief Division assignment
  FINumber& operator/=(const FINumber& x) {
    boost::optional< FBound > d = x.singleton(); // FBound
    if (d && (*d).is_zero()) {
      // [_, _] / 0 = ⊥
      this->_lb = 1;
      this->_ub = 0;
    } else if (x.contains(0)) {
      boost::optional< FBound > n = this->singleton();
      if (n && (*n).is_zero()) {
        // 0 / [_, _] = 0
        this->_lb = 0;
        this->_ub = 0;
      } else {
        // ([_,_]) / ([_,0] join [0,_]) = top
        this->_lb = FBound::minus_infinity();
        this->_ub = FBound::plus_infinity();
      }
    } else {
      FBound ll = this->lb() / x.lb();
      FBound lu = this->lb() / x.ub();
      FBound ul = this->ub() / x.lb();
      FBound uu = this->ub() / x.ub();
      this->_lb = min(ll, lu, ul, uu);
      this->_ub = max(ll, lu, ul, uu);
    }
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

  /// \brief Return a string representation of the floating point number in the
  /// given base
  std::string str() const {
    if (this->_lb.number().is_initialized() &&
        this->_ub.number().is_initialized()) {
      return ("[" + this->_lb.number()->str() + "," +
              this->_ub.number()->str() + "]");
    } else {
      return "none";
    }
  }

  /// @}
  /// \name Unary Operators
  /// @{

  /// \brief Set the floating point interval number to [0,0]
  FINumber& set_zero() {
    this->_lb = 0;
    this->_ub = 0;
    return *this;
  }

  /// \brief Unary minus
  const FINumber operator-() const {
    if (this->is_bottom()) {
      return bottom();
    } else {
      return FINumber(-this->_ub, -this->_lb);
    }
  }

  /// \brief If the interval is a singleton [n, n], return n, otherwise return
  /// boost::none
  boost::optional< FBound > singleton() const {
    if (this->_lb.is_finite() && this->_lb == this->_ub) {
      return this->_lb;
    } else {
      return boost::none;
    }
  }

  /// \brief Return true if the interval contains n
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  bool contains(T n) const {
    return this->contains(FNumber(n));
  }

  /// \brief Return true if the interval contains n
  bool contains(FNumber n) const {
    if (this->is_bottom()) {
      return false;
    } else {
      FBound b(std::move(n));
      return this->_lb <= b && b <= this->_ub;
    }
  }

public:
  // friends

  friend FINumber add(const FINumber& lhs, const FINumber& rhs);

  friend FINumber operator+(const FINumber& lhs, const FINumber& rhs);

  friend FINumber sub(const FINumber& lhs, const FINumber& rhs);

  friend FINumber operator-(const FINumber& lhs, const FINumber& rhs);

  friend FINumber mul(const FINumber& lhs, const FINumber& rhs);

  friend FINumber operator*(const FINumber& lhs, const FINumber& rhs);

  friend FINumber div(const FINumber& lhs, const FINumber& rhs);

  friend FINumber operator/(const FINumber& lhs, const FINumber& rhs);

  friend bool operator==(const FINumber& lhs, const FINumber& rhs);

  friend bool operator!=(const FINumber& lhs, const FINumber& rhs);

  friend bool operator<(const FINumber& lhs, const FINumber& rhs);

  friend bool operator<=(const FINumber& lhs, const FINumber& rhs);

  friend bool operator>(const FINumber& lhs, const FINumber& rhs);

  friend bool operator>=(const FINumber& lhs, const FINumber& rhs);

  friend std::ostream& operator<<(std::ostream& o, const FINumber& n);

  friend std::size_t hash_value(const FINumber&);
};    /// end class FINumber

/// \name Binary Operators
/// @{

/// \brief Addition
///
/// Returns the sum of the operands
inline FINumber add(const FINumber& lhs, const FINumber& rhs) {
  return FINumber(lhs._lb + rhs._lb, lhs._ub + rhs._ub);
}

/// \brief Addition
///
/// Returns the sum of the operands
inline FINumber operator+(const FINumber& lhs, const FINumber& rhs) {
  return add(lhs, rhs);
}

/// \brief Subtraction
///
/// Returns the difference of the operands
inline FINumber sub(const FINumber& lhs, const FINumber& rhs) {
  return FINumber(lhs._lb - rhs._ub, lhs._ub - rhs._lb);
}

/// \brief Subtraction
///
/// Returns the sum of the operands
inline FINumber operator-(const FINumber& lhs, const FINumber& rhs) {
  return sub(lhs, rhs);
}

/// \brief Multiplication
///
/// Returns the product of the operands
inline FINumber mul(const FINumber& lhs, const FINumber& rhs) {
  if (lhs.is_bottom() || rhs.is_bottom()) {
    return FINumber::bottom();
  } else {
    FBound ll = lhs.lb() * rhs.lb();
    FBound lu = lhs.lb() * rhs.ub();
    FBound ul = lhs.ub() * rhs.lb();
    FBound uu = lhs.ub() * rhs.ub();
    return FINumber(min(ll, lu, ul, uu), max(ll, lu, ul, uu));
  }
}

/// \brief Multiplication
///
/// Returns the product of the operands
inline FINumber operator*(const FINumber& lhs, const FINumber& rhs) {
  return mul(lhs, rhs);
}

/// \brief Division
///
/// Returns the quotient of the operands
inline FINumber div(const FINumber& lhs, const FINumber& rhs) {
  boost::optional< FBound > d = rhs.singleton(); // FBound
  if (d && (*d).is_zero()) {
    // [_, _] / 0 = ⊥
    return FINumber::bottom();
  } else if (rhs.contains(0)) {
    boost::optional< FBound > n = lhs.singleton();
    if (n && (*n).is_zero()) {
      // 0 / [_, _] = 0
      return FINumber(0);
    } else {
      // ([_,_]) / ([_,0] join [0,_]) = top
      return FINumber::top();
    }
  } else {
    FBound ll = lhs.lb() / rhs.lb();
    FBound lu = lhs.lb() / rhs.ub();
    FBound ul = lhs.ub() / rhs.lb();
    FBound uu = lhs.ub() / rhs.ub();
    return FINumber(min(ll, lu, ul, uu), max(ll, lu, ul, uu));
  }
}

/// \brief Division
///
/// Returns the quotient of the operands
inline FINumber operator/(const FINumber& lhs, const FINumber& rhs) {
  return div(lhs, rhs);
}

/// @}
/// \name Comparison Operators
/// @{

/// \brief Equality operator
inline bool operator==(const FINumber& lhs, const FINumber& rhs) {
  return (lhs._lb == rhs._lb && lhs._ub == rhs._ub);
}

/// \brief Equality operator
inline bool operator!=(const FINumber& lhs, const FINumber& rhs) {
  return (lhs._lb != rhs._lb || lhs._ub != rhs._ub);
}

/// \brief Less than comparison with floating point number types
inline bool operator<(const FINumber& lhs, const FINumber& rhs) {
  return (lhs._lb > rhs._lb && lhs._ub < rhs._ub);
}

/// \brief Less or equal than comparison with floating point number types
inline bool operator<=(const FINumber& lhs, const FINumber& rhs) {
  return (lhs._lb >= rhs._lb && lhs._ub <= rhs._ub);
}

/// \brief Greater than comparison with floating point number types
inline bool operator>(const FINumber& lhs, const FINumber& rhs) {
  return (lhs._lb < rhs._lb && lhs._ub > rhs._ub);
}

/// \brief Greater or equal than comparison with floating point number types
inline bool operator>=(const FINumber& lhs, const FINumber& rhs) {
  return (lhs._lb <= rhs._lb && lhs._ub >= rhs._ub);
}

/// @}
/// \name Input / Output
/// @{

/// \brief Write a floating point number on a stream
inline std::ostream& operator<<(std::ostream& o, const FINumber& n) {
  std::cout.precision(30);
  o << "[" << n._lb << "," << n._ub << "]";
  return o;
}

/// @}

/// \brief Return the hash of a FNumber
inline std::size_t hash_value(const FINumber& n) {
  std::size_t hash = 0;
  boost::hash_combine(hash, n);
  boost::hash_combine(hash, n._bit_width);
  boost::hash_combine(hash, n._sign);
  return hash;
}
} // end namespace core
} // end namespace ikos

namespace std {

/// \brief Hash for FINumber
template <>
struct hash< ikos::core::FINumber > {
  std::size_t operator()(const ikos::core::FINumber& n) const {
    return ikos::core::hash_value(n);
  }
};

} // end namespace std
