//
// Created by zou on 3/8/24.
//

#pragma once

#include <ikos/core/number/bound.hpp> // By zoush99
#include <ikos/core/number/signedness.hpp>
#include <ikos/core/number/supported_integralorfloat.hpp>
// #include <iostream>
#include <cmath>
namespace ikos {
namespace core {

/// \brief Relative error
struct relativeError {
  float floatlRE = 1 - pow(2, -23);
  float floatrRE = 1 + pow(2, -23);
  double doublelRE = 1 - pow(2, -52);
  double doublerRE = 1 + pow(2, -52);
} RelativeError;

/// \brief Absolute error
struct absoluteError {
  float floatlAE = -pow(2, -149);
  float floatrAE = pow(2, -149);
  double doublelAE = -pow(2, -1074);
  double doublerAE = pow(2, -1074);
} AbsoluteError;

/// \brief Class for floating point interval numbers
class FRINumber {
private:
  FBound _lb; /// [_lb,_ub]: [FNumber,FNumber]
  FBound _ub;
  uint64_t _bit_width;
  Signedness _sign;

private:
  struct TopTag {};
  struct BottomTag {};

  /// \brief Create the top floating point interval number [-oo, +oo]
  explicit FRINumber(TopTag)
      : _lb(FBound ::minus_infinity()), _ub(FBound ::plus_infinity()) {}

  /// \brief Create the bottom floating point interval number
  explicit FRINumber(BottomTag) : _lb(1), _ub(0) {}

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
  static FRINumber top() { return FRINumber(TopTag{}); }

  /// \brief Create the bottom floating point interval number
  static FRINumber bottom() { return FRINumber(BottomTag{}); }

  /// \name Constructors
  /// @{

  /// \brief Default constructor
  FRINumber() : _lb(1), _ub(1), _bit_width(32), _sign(Signed) {}

  /// \brief Create a floating point interval number from a type
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FRINumber(T v, uint64_t bit_width, Signedness sign)
      : _lb(v), _ub(v), _bit_width(bit_width), _sign(sign) {}

  /// \brief Label that require abstraction
  /// \brief Create a floating point interval number from a type
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FRINumber(T v, uint64_t bit_width, Signedness sign, AbstractTag)
      : _bit_width(bit_width), _sign(sign) {
    if (std::is_same< T, float >::value ||
        std::is_same< T, int >::value) { // fl
      this->_lb = std::move(
          FBound(v * RelativeError.floatlRE + AbsoluteError.floatlAE));
      this->_ub = std::move(
          FBound(v * RelativeError.floatrRE + AbsoluteError.floatrAE));
    } else { // do
      this->_lb = std::move(
          FBound(v * RelativeError.doublelRE + AbsoluteError.doublelAE));
      this->_ub = std::move(
          FBound(v * RelativeError.doublerRE + AbsoluteError.doublerAE));
    }
  }

  /// \brief Create a floating point interval number from a type
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FRINumber(T v) : _lb(v), _ub(v), _sign(Signed) {
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
  FRINumber(T v, AbstractTag) : _sign(Signed) {
    if (std::is_same< T, float >::value ||
        std::is_same< T, int >::value) { // fl
      this->_bit_width = 32;
      this->_lb = std::move(
          FBound(v * RelativeError.floatlRE + AbsoluteError.floatlAE));
      this->_ub = std::move(
          FBound(v * RelativeError.floatrRE + AbsoluteError.floatrAE));
    } else { // do
      this->_bit_width = 64;
      this->_lb = std::move(
          FBound(v * RelativeError.doublelRE + AbsoluteError.doublelAE));
      this->_ub = std::move(
          FBound(v * RelativeError.doublerRE + AbsoluteError.doublerAE));
    }
  }

  /// \brief Create a floating point interval number from a type
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FRINumber(T lb, T ub, uint64_t bit_width, Signedness sign)
      : _lb(lb), _ub(ub), _bit_width(bit_width), _sign(sign) {}

  /// \brief Create a floating point interval number from a type
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FRINumber(T lb, T ub) : _lb(lb), _ub(ub), _sign(Signed) {
    if (std::is_same< T, float >::value ||
        std::is_same< T, int >::value) { // fl
      this->_bit_width = 32;
    } else { // do
      this->_bit_width = 64;
    }
  }

  /// \brief Create a floating pointer interval number from a FNumber
  FRINumber(FNumber v) {
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
  FRINumber(FNumber v, AbstractTag) {
    if (v.bit_width() == 32) { // fl
      this->_lb = std::move(FBound(v.value< float >() * RelativeError.floatlRE +
                                   AbsoluteError.floatlAE));
      this->_ub = std::move(FBound(v.value< float >() * RelativeError.floatrRE +
                                   AbsoluteError.floatrAE));
    } else if (v.bit_width() == 64) { // do
      this->_lb =
          std::move(FBound(v.value< double >() * RelativeError.doublelRE +
                           AbsoluteError.doublelAE));
      this->_ub =
          std::move(FBound(v.value< double >() * RelativeError.doublerRE +
                           AbsoluteError.doublerAE));
    } else {
      this->_lb = this->_ub = 1;
    }
    this->_bit_width = v.bit_width();
  }

  /// \brief Create a floating pointer interval number from FNumbers
  FRINumber(FNumber lb, FNumber ub, uint64_t bit_width, Signedness sign)
      : _lb(lb), _ub(ub), _bit_width(bit_width), _sign(sign) {}

  /// \brief Create a floating pointer interval number from FNumbers
  FRINumber(FNumber lb, FNumber ub)
      : _lb(lb), _ub(ub), _bit_width(lb.bit_width()), _sign(Signed) {}

  /// \brief Create a floating pointer interval number from a Fbound
  FRINumber(FBound v) {
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
  FRINumber(FBound v, AbstractTag) {
    if (v.number().is_initialized() &&
        v.number()->bit_width() == 32) { // x is not empty and fl
      this->_lb = std::move(
          FBound(v.number()->value< float >() * RelativeError.floatlRE +
                 AbsoluteError.floatlAE));
      this->_ub = std::move(
          FBound(v.number()->value< float >() * RelativeError.floatrRE +
                 AbsoluteError.floatrAE));
    } else if (v.number().is_initialized() &&
               v.number()->bit_width() == 64) { // x is not empty and do
      this->_lb = std::move(
          FBound(v.number()->value< double >() * RelativeError.doublelRE +
                 AbsoluteError.doublelAE));
      this->_ub = std::move(
          FBound(v.number()->value< double >() * RelativeError.doublerRE +
                 AbsoluteError.doublerAE));
    } else { // none
      this->_lb = this->_ub = 1;
    }
  }

  /// \brief Create a floating pointer interval number from FBounds
  FRINumber(FBound lb, FBound ub, uint64_t bit_width, Signedness sign)
      : _lb(lb), _ub(ub), _bit_width(bit_width), _sign(sign) {}

  /// \brief Create a floating pointer interval number from Fbounds
  FRINumber(FBound lb, FBound ub) : _lb(lb), _ub(ub), _sign(Signed) {
    if (lb.number().is_initialized() &&
        ub.number().is_initialized()) { // lb and ub are not empty
      this->_bit_width = lb.number()->bit_width();
    } else { // none
      this->_bit_width = 0;
    }
  }

public:
  /// \brief Copy constructor
  FRINumber(const FRINumber& o)
      : _lb(o._lb), _ub(o._ub), _bit_width(o._bit_width), _sign(o._sign) {}

  /// \brief Move constructor
  FRINumber(FRINumber&& o) noexcept
      : _lb(o._lb), _ub(o._ub), _bit_width(o._bit_width), _sign(o._sign) {
    o._bit_width = 0; // do not delete o
  }

  /// \brief Destructor
  ~FRINumber() = default;

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
  static FRINumber zero(uint64_t bit_width, Signedness sign) {
    ikos_assert_msg(bit_width > 0, "invalid bit width");

    return FRINumber(0, 0, bit_width, sign);
  }

  /// @}
  /// \name Assignment Operators
  /// @{

  /// \brief Copy assignment
  FRINumber& operator=(const FRINumber& o) {
    if (this == &o) {
      return *this;
    }

    this->_lb = o._lb;
    this->_ub = o._ub;
    return *this;
  }

  /// \brief Move assignment
  FRINumber& operator=(FRINumber&& o) noexcept {
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
  FRINumber& operator=(T n) {
    this->_lb = std::move(FBound(n));
    this->_ub = std::move(FBound(n));
    if (std::is_same< T, float >::value ||
        std::is_same< T, int >::value) { // fl
      this->_bit_width = 32;
    } else { // do
      this->_bit_width = 64;
    }
    return *this;
  }

  /// \brief Addition assignment
  FRINumber& operator+=(const FRINumber& x) {
    this->_lb += x._lb;
    this->_ub += x._ub;
    return *this;
  }

  /// \brief Subtraction assignment
  FRINumber& operator-=(const FRINumber& x) {
    this->_lb -= x._ub;
    this->_ub -= x._lb;
    return *this;
  }

  /// \brief Multiplication assignment
  FRINumber& operator*=(const FRINumber& x) {
    FBound ll = this->lb() * x.lb();
    FBound lu = this->lb() * x.ub();
    FBound ul = this->ub() * x.lb();
    FBound uu = this->ub() * x.ub();
    this->_lb = min(ll, lu, ul, uu);
    this->_ub = max(ll, lu, ul, uu);
    return *this;
  }

  /// \brief Division assignment
  FRINumber& operator/=(const FRINumber& x) {
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
  FRINumber& set_zero() {
    this->_lb = 0;
    this->_ub = 0;
    return *this;
  }

  /// \brief Unary minus
  const FRINumber operator-() const {
    if (this->is_bottom()) {
      return bottom();
    } else {
      return FRINumber(-this->_ub, -this->_lb);
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

  friend FRINumber add(const FRINumber& lhs, const FRINumber& rhs);

  friend FRINumber addFNu(const FNumber& lhs, const FNumber& rhs);

  friend FRINumber addFBo(const FBound & lhs, const FBound & rhs);

  friend FRINumber operator+(const FRINumber& lhs, const FRINumber& rhs);

  friend FRINumber sub(const FRINumber& lhs, const FRINumber& rhs);

  friend FRINumber subFNu(const FNumber& lhs, const FNumber& rhs);

  friend FRINumber subFBo(const FBound & lhs, const FBound & rhs);

  friend FRINumber operator-(const FRINumber& lhs, const FRINumber& rhs);

  friend FRINumber mul(const FRINumber& lhs, const FRINumber& rhs);

  friend FRINumber mulFNu(const FNumber& lhs, const FNumber& rhs);

  friend FRINumber mulFBo(const FBound & lhs, const FBound & rhs);

  friend FRINumber operator*(const FRINumber& lhs, const FRINumber& rhs);

  friend FRINumber div(const FRINumber& lhs, const FRINumber& rhs);

  friend FRINumber divFNu(const FNumber& lhs, const FNumber& rhs);

  friend FRINumber divFBo(const FBound & lhs, const FBound & rhs);

  friend FRINumber operator/(const FRINumber& lhs, const FRINumber& rhs);

  friend bool operator==(const FRINumber& lhs, const FRINumber& rhs);

  friend bool operator!=(const FRINumber& lhs, const FRINumber& rhs);

  friend bool operator<(const FRINumber& lhs, const FRINumber& rhs);

  friend bool operator<=(const FRINumber& lhs, const FRINumber& rhs);

  friend bool operator>(const FRINumber& lhs, const FRINumber& rhs);

  friend bool operator>=(const FRINumber& lhs, const FRINumber& rhs);

  friend std::ostream& operator<<(std::ostream& o, const FRINumber& n);

  friend std::size_t hash_value(const FRINumber&);
}; /// end class FRINumber

/// \name Binary Operators
/// @{

/// \brief Addition
///
/// Returns the sum of the operands
inline FRINumber add(const FRINumber& lhs, const FRINumber& rhs) {
  return FRINumber(lhs._lb + rhs._lb, lhs._ub + rhs._ub);
}

/// \todo Here I need to modify the binary of two floating point types. By zoush99
/// Subtraction, multiplication and division are also required
inline FRINumber addFNu(const FNumber& lhs, const FNumber& rhs) {
  FRINumber Flhs(lhs);
  FRINumber Frhs(rhs);
  FRINumber Res=Flhs+Frhs;
  return Res;
}

/// \brief Addition
///
/// Returns the sum of the operands
inline FRINumber operator+(const FRINumber& lhs, const FRINumber& rhs) {
  return add(lhs, rhs);
}

/// \brief Subtraction
///
/// Returns the difference of the operands
inline FRINumber sub(const FRINumber& lhs, const FRINumber& rhs) {
  return FRINumber(lhs._lb - rhs._ub, lhs._ub - rhs._lb);
}

/// \brief Subtraction
///
/// Returns the sum of the operands
inline FRINumber operator-(const FRINumber& lhs, const FRINumber& rhs) {
  return sub(lhs, rhs);
}

/// \brief Multiplication
///
/// Returns the product of the operands
inline FRINumber mul(const FRINumber& lhs, const FRINumber& rhs) {
  if (lhs.is_bottom() || rhs.is_bottom()) {
    return FRINumber::bottom();
  } else {
    FBound ll = lhs.lb() * rhs.lb();
    FBound lu = lhs.lb() * rhs.ub();
    FBound ul = lhs.ub() * rhs.lb();
    FBound uu = lhs.ub() * rhs.ub();
    return FRINumber(min(ll, lu, ul, uu), max(ll, lu, ul, uu));
  }
}

/// \brief Multiplication
///
/// Returns the product of the operands
inline FRINumber operator*(const FRINumber& lhs, const FRINumber& rhs) {
  return mul(lhs, rhs);
}

/// \brief Division
///
/// Returns the quotient of the operands
inline FRINumber div(const FRINumber& lhs, const FRINumber& rhs) {
  boost::optional< FBound > d = rhs.singleton(); // FBound
  if (d && (*d).is_zero()) {
    // [_, _] / 0 = ⊥
    return FRINumber::bottom();
  } else if (rhs.contains(0)) {
    boost::optional< FBound > n = lhs.singleton();
    if (n && (*n).is_zero()) {
      // 0 / [_, _] = 0
      return FRINumber(0);
    } else {
      // ([_,_]) / ([_,0] join [0,_]) = top
      return FRINumber::top();
    }
  } else {
    FBound ll = lhs.lb() / rhs.lb();
    FBound lu = lhs.lb() / rhs.ub();
    FBound ul = lhs.ub() / rhs.lb();
    FBound uu = lhs.ub() / rhs.ub();
    return FRINumber(min(ll, lu, ul, uu), max(ll, lu, ul, uu));
  }
}

/// \brief Division
///
/// Returns the quotient of the operands
inline FRINumber operator/(const FRINumber& lhs, const FRINumber& rhs) {
  return div(lhs, rhs);
}

/// @}
/// \name Comparison Operators
/// @{

/// \brief Equality operator
inline bool operator==(const FRINumber& lhs, const FRINumber& rhs) {
  return (lhs._lb == rhs._lb && lhs._ub == rhs._ub);
}

/// \brief Equality operator
inline bool operator!=(const FRINumber& lhs, const FRINumber& rhs) {
  return (lhs._lb != rhs._lb || lhs._ub != rhs._ub);
}

/// \brief Less than comparison with floating point number types
inline bool operator<(const FRINumber& lhs, const FRINumber& rhs) {
  return (lhs._lb > rhs._lb && lhs._ub < rhs._ub);
}

/// \brief Less or equal than comparison with floating point number types
inline bool operator<=(const FRINumber& lhs, const FRINumber& rhs) {
  return (lhs._lb >= rhs._lb && lhs._ub <= rhs._ub);
}

/// \brief Greater than comparison with floating point number types
inline bool operator>(const FRINumber& lhs, const FRINumber& rhs) {
  return (lhs._lb < rhs._lb && lhs._ub > rhs._ub);
}

/// \brief Greater or equal than comparison with floating point number types
inline bool operator>=(const FRINumber& lhs, const FRINumber& rhs) {
  return (lhs._lb <= rhs._lb && lhs._ub >= rhs._ub);
}

/// @}
/// \name Input / Output
/// @{

/// \brief Write a floating point number on a stream
inline std::ostream& operator<<(std::ostream& o, const FRINumber& n) {
  std::cout.precision(30);
  o << "[" << n._lb << "," << n._ub << "]";
  return o;
}

/// @}
/// \brief Return the hash of a FNumber
inline std::size_t hash_value(const FRINumber& n) {
  std::size_t hash = 0;
  boost::hash_combine(hash, n);
  boost::hash_combine(hash, n._bit_width);
  boost::hash_combine(hash, n._sign);
  return hash;
}

}; // namespace core

}; // namespace ikos
