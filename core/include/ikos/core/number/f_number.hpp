//
// Created by zou on 2/20/24.
//

#pragma once

#include <llvm-14/llvm/ADT/APFloat.h> // By zoush99
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
  FNumber() {
    llvm::APFloat N(1.0f);
    _n = N;
    _bit_width = 32;
    _sign = Signedness::Signed;
  }

  /// \brief Create a floating point number from a type
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FNumber(T n, uint64_t bit_width, Signedness sign)
      : _bit_width(bit_width), _sign(sign) {
    ikos_assert_msg((bit_width == 32 || bit_width == 64), "invalid bit width");

    if (std::is_same< T, float >::value ||
        std::is_same< T, int >::value) { // fl or int
      this->_n = llvm::APFloat(static_cast< float >(n));
    } else { // do
      this->_n = llvm::APFloat(static_cast< double >(n));
    }
  }

  /// \brief Create a floating point number from a type
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FNumber(T n, uint64_t bit_width, Signedness sign, NormalizedTag)
      : _bit_width(bit_width), _sign(sign) {
    ikos_assert_msg((bit_width == 32 || bit_width == 64), "invalid bit width");

    if (std::is_same< T, float >::value ||
        std::is_same< T, int >::value) { // fl or int
      this->_n = llvm::APFloat(static_cast< float >(n));
    } else { // do
      this->_n = llvm::APFloat(static_cast< double >(n));
    }
  }

  /// \brief Create a floating point number from a ZNumber
  FNumber(const ZNumber& n, uint64_t bit_width, Signedness sign)
      : _bit_width(bit_width), _sign(sign) {
    ikos_assert_msg((bit_width == 32 || bit_width == 64), "invalid bit width");
    this->_n = llvm::APFloat(static_cast< float >(n.to< int >()));
  }

  /// \brief Create a floating point number from a ZNumber
  FNumber(const ZNumber& n, uint64_t bit_width, Signedness sign, NormalizedTag)
      : _bit_width(bit_width), _sign(sign) {
    ikos_assert_msg((bit_width == 32 || bit_width == 64), "invalid bit width");
    this->_n = llvm::APFloat(static_cast< float >(n.to< int >()));
  }

  /// \brief Create a floating point number from a type
  template <
      typename T,
      class = std::enable_if_t< IsSupportedIntegralOrFloat< T >::value > >
  FNumber(T n) : _sign(Signed) {
    if (std::is_same< T, float >::value ||
        std::is_same< T, int >::value) { // fl
      _bit_width = 32;
      this->_n = llvm::APFloat(static_cast< float >(n));
    } else { // do
      _bit_width = 64;
      this->_n = llvm::APFloat(static_cast< double >(n));
    }
  }

  /// \brief Create a floating point number from a llvm::APFloat class
  FNumber(llvm::APFloat& n,uint64_t bit_width):_n(n),_bit_width(bit_width),_sign(Signedness::Signed){}

public:
  /// \brief Copy constructor
  FNumber(const FNumber& o) : _bit_width(o._bit_width), _sign(o._sign) {
    this->_n = o._n;
  }

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
      return FNumber(-3.4028235E38, 32, sign);
    } else { // do
      return FNumber(-1.7976931348623157E308, 64, sign);
    }
  }

  /// \brief Create the maximum machine integer for the given bit width and sign
  static FNumber max(uint64_t bit_width, Signedness sign) {
    ikos_assert_msg(bit_width > 0, "invalid bit width");
    // By default, all are signed.
    if (bit_width == 32) { // fl
      return FNumber(3.4028235E38, 32, sign, NormalizedTag{});
    } else { // do
      return FNumber(1.7976931348623157E308, 64, sign, NormalizedTag{});
    }
  }

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

  /// \brief It is aimed at normalized numbers and does not consider denormalized numbers.
  /// \brief Return true if this is the minimum machine integer
  bool is_min() const {
    if (this->_bit_width==32) { // fl
      return this->_n==llvm::APFloat(-3.4028235E38);
    } else {  // do
      return this->_n==llvm::APFloat(-1.7976931348623157E308);
    }
  }

  /// \brief Return true if this is the maximum machine integer
  bool is_max() const {
    if (this->_bit_width==32) { // fl
      return this->_n==llvm::APFloat(3.4028235E38);
    } else {  // do
      return this->_n==llvm::APFloat(1.7976931348623157E308);
    }
  }

  /// \brief Return true if the machine integer is 0
  bool is_zero() const {
      return this->_n.isZero();
  }

  /// @}
  /// \name Unary Operators
  /// @{

  /// \brief Set the floating point number to zero
  void set_zero() {
      this->_n==llvm::APFloat(0.0f);
  }

  /// \todo
  /// \brief Unary minus
  const FNumber operator-() {
      return FNumber(this->_n, this->_bit_width);
  }

  /// \brief Truncate the floating point number to the given bit width

  /// \brief Extend the floating point number to the given bit width

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

} // namespace core
} // namespace ikos