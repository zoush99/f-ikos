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
      if (o.is_fl()) {  // do = fl
        this->_n.d = static_cast< double >(o._n.f);
      } else {  // do = do
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
  template < typename T,
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
  FNumber& operator+=(const FNumber& x){
    if (this->is_fl()) {
      if(x.is_fl()){  // fl += fl
        this->_n.f += x._n.f;
      }else{  // fl += do
        this->_n.f += static_cast<float>(x._n.d);
      }
    } else {
      if(x.is_fl()){  // do += fl
        this->_n.d += static_cast<double >(x._n.f);
      } else{ // do += do
        this->_n.d += x._n.d;
      }
    }
    return *this;
  }

  /// \brief Subtraction assignment
  FNumber& operator-=(const FNumber& x){
    if (this->is_fl()) {
      if(x.is_fl()){  // fl -= fl
        this->_n.f -= x._n.f;
      }else{  // fl -= do
        this->_n.f -= static_cast<float>(x._n.d);
      }
    } else {
      if(x.is_fl()){  // do -= fl
        this->_n.d -= static_cast<double >(x._n.f);
      } else{ // do -= do
        this->_n.d -= x._n.d;
      }
    }
    return *this;
  }

}; // end class FNumber

} // end namespace core
} // end namespace ikos
