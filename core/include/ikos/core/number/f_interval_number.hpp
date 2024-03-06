//
// Created by zou on 3/4/24.
//

#pragma once

#include <ikos/core/number/bound.hpp> // By zoush99
#include <ikos/core/number/signedness.hpp>
#include <ikos/core/number/supported_integralorfloat.hpp>

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
  struct TopTag {};
  struct BottomTag {};
  struct AbstractTag{};

  /// \brief Create the top floating point interval number [-oo, +oo]
  explicit FINumber(TopTag)
      : _lb(FBound ::minus_infinity()), _ub(FBound ::plus_infinity()) {}

  /// \brief Create the bottom floating point interval number
  explicit FINumber(BottomTag) : _lb(1), _ub(0) {}

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

  /// \todo
  /// \brief Create a floating point interval number from a type
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FINumber(T v, uint64_t bit_width, Signedness sign,AbstractTag)
      : _lb(v), _ub(v), _bit_width(bit_width), _sign(sign) {}

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
    this->_lb = n;
    this->_ub = n;
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
      this->_lb=min(ll, lu, ul, uu);
      this->_ub=max(ll, lu, ul, uu);
    return *this;
  }

  /// \todo
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
      return FINumber(-this->_ub,-this->_lb);
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
};
// end class FINumber

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

/*/// \brief Division
///
/// Returns the quotient of the operands
/// \todo bugs here!!!
inline FINumber div(const FINumber& lhs,const FINumber& rhs){
  if (lhs.is_bottom() || rhs.is_bottom()) {
    return FINumber::bottom();
  } else {
    boost::optional< FBound> d = rhs.singleton();
    if (d && *d == 0) {
      // [_, _] / 0 = ⊥
      return FINumber::bottom();
    } else if (rhs.contains(0)) {
      boost::optional< FBound > n = lhs.singleton();
      if (n && *n == 0) {
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
}

/// \brief Division
///
/// Returns the quotient of the operands
inline FINumber operator/(const FINumber& lhs,const FINumber& rhs){
  return div(lhs,rhs);
}*/

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
  o << "[" << n._lb << "," << n._ub << "]";
  return o;
}

/// @}

/// \todo
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