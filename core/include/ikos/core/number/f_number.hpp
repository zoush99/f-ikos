//
// Created by zou on 1/7/24.
//

#pragma once

#include <ikos/core/number/compatibility.hpp>
#include <ikos/core/number/signedness.hpp>
#include <ikos/core/number/supported_integral.hpp>
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

public:
  /// \name Constructors
  /// @{

  /// \brief Default constructor
  FNumber() = delete;

private:
  /// \brief To harmonize with machine integer types
  struct NormalizedTag{};

  /// \brief Create a floating point number from an integral type
  template < typename T,
             class = std::enable_if_t< IsSupportedIntegral< T >::value > >
  FNumber(T n, uint64_t bit_width, Signedness sign,NormalizedTag)
      : _bit_width(bit_width), _sign(sign) {
    ikos_assert_msg((bit_width == 32 || bit_width == 64), "invalid bit width");

    if (this->is_fl()) {
      this->_n.f = static_cast< float >(n);
    } else {
      this->_n.d = static_cast< double >(n);
    }
  }

  /// \brief Create a floating point number from a ZNumber
  FNumber(const ZNumber& n, uint64_t bit_width, Signedness sign, NormalizedTag):_bit_width(bit_width),_sign(sign){
    ikos_assert_msg((bit_width == 32 || bit_width == 64), "invalid bit width");
    if (this->is_fl()) {
      this->_n.f = n.to<int>();
    } else {
      this->_n.d = n.to<int>();
    }
  }

public:
  /// \brief Copy constructor
  FNumber(const FNumber& o):_bit_width(o._bit_width),_sign(o._sign){
    if (o.is_fl()) {
      this->_n.f = o._n.f;
    } else {
      this->_n.d = o._n.d;
    }
  }

}; // end class FNumber

} // end namespace core
} // end namespace ikos
