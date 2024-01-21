//
// Created by zou on 1/21/24.
//

/*******************************************************************************
 *
 * \file
 * \brief Machine integer scalar abstract domain
 *
 * Author: Maxime Arthaud
 *
 * Contact: ikos@lists.nasa.gov
 *
 * Notices:
 *
 * Copyright (c) 2019 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Disclaimers:
 *
 * No Warranty: THE SUBJECT SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY OF
 * ANY KIND, EITHER EXPRESSED, IMPLIED, OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL CONFORM TO SPECIFICATIONS,
 * ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
 * OR FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL BE
 * ERROR FREE, OR ANY WARRANTY THAT DOCUMENTATION, IF PROVIDED, WILL CONFORM TO
 * THE SUBJECT SOFTWARE. THIS AGREEMENT DOES NOT, IN ANY MANNER, CONSTITUTE AN
 * ENDORSEMENT BY GOVERNMENT AGENCY OR ANY PRIOR RECIPIENT OF ANY RESULTS,
 * RESULTING DESIGNS, HARDWARE, SOFTWARE PRODUCTS OR ANY OTHER APPLICATIONS
 * RESULTING FROM USE OF THE SUBJECT SOFTWARE.  FURTHER, GOVERNMENT AGENCY
 * DISCLAIMS ALL WARRANTIES AND LIABILITIES REGARDING THIRD-PARTY SOFTWARE,
 * IF PRESENT IN THE ORIGINAL SOFTWARE, AND DISTRIBUTES IT "AS IS."
 *
 * Waiver and Indemnity:  RECIPIENT AGREES TO WAIVE ANY AND ALL CLAIMS AGAINST
 * THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL
 * AS ANY PRIOR RECIPIENT.  IF RECIPIENT'S USE OF THE SUBJECT SOFTWARE RESULTS
 * IN ANY LIABILITIES, DEMANDS, DAMAGES, EXPENSES OR LOSSES ARISING FROM SUCH
 * USE, INCLUDING ANY DAMAGES FROM PRODUCTS BASED ON, OR RESULTING FROM,
 * RECIPIENT'S USE OF THE SUBJECT SOFTWARE, RECIPIENT SHALL INDEMNIFY AND HOLD
 * HARMLESS THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS,
 * AS WELL AS ANY PRIOR RECIPIENT, TO THE EXTENT PERMITTED BY LAW.
 * RECIPIENT'S SOLE REMEDY FOR ANY SUCH MATTER SHALL BE THE IMMEDIATE,
 * UNILATERAL TERMINATION OF THIS AGREEMENT.
 *
 ******************************************************************************/

#pragma once

#include <ikos/core/domain/numeric/abstract_domain.hpp> // By zoush99
#include <ikos/core/domain/scalar/abstract_domain.hpp>
#include <ikos/core/domain/uninitialized/abstract_domain.hpp>

namespace ikos {
namespace core {
namespace scalar {

/// \brief Machine integer scalar abstract domain
///
/// This class implements a scalar abstract domain that handles machine integers
/// and ignore floating points and pointers safely.
template < typename VariableRef,
           typename MemoryLocationRef,
           typename UninitializedDomain,
           typename NumericDomainT >
class NumericDomain final
    : public scalar::AbstractDomain< VariableRef,
                                     MemoryLocationRef,
                                     NumericDomain< VariableRef,
                                                    MemoryLocationRef,
                                                    UninitializedDomain,
                                                    NumericDomainT > > {
public:
  static_assert(
      uninitialized::IsAbstractDomain< UninitializedDomain,
                                       VariableRef >::value,
      "UninitializedDomain must implement uninitialized::AbstractDomain");
  static_assert(
      numeric::IsAbstractDomain< NumericDomainT, FNumber, VariableRef >::value,
      "MachineIntDomain must implement machine_int::AbstractDomain");

public:
  using PointerPredicate = pointer::Predicate;
  using PointsToSetT = PointsToSet< MemoryLocationRef >;
  using PointerAbsValueT = PointerAbsValue< MemoryLocationRef >;
  using PointerSetT = PointerSet< MemoryLocationRef >;

  // By zoush99
  using FnuBinaryOperator = numeric::BinaryOperator;
  using FnuPredicate = numeric::Predicate;
  using FnuLinearExpression = LinearExpression< FNumber, VariableRef >;
  using FnuInterval = numeric::Interval< FNumber >;
  using FnuCongruence = numeric::Congruence< FNumber >;
  using FnuIntervalCongruence = numeric::IntervalCongruence< FNumber >;

private:
  using IntVariableTrait = machine_int::VariableTraits< VariableRef >;
  using ScalarVariableTrait = scalar::VariableTraits< VariableRef >;

private:
  /// \brief Underlying uninitialized abstract domains
  UninitializedDomain _uninitialized;

  /// \brief Underlying machine integer abstract domains
  NumericDomainT _numeric;

public:
  /// \brief Create an abstract value with the given underlying abstract values
  ///
  /// \param uninitialized The uninitialized abstract value
  /// \param integer The machine integer abstract value
  NumericDomain(UninitializedDomain uninitialized, NumericDomainT numeric)
      : _uninitialized(std::move(uninitialized)), _numeric(std::move(numeric)) {
    this->normalize();
  }

  /// \brief Copy constructor
  NumericDomain(const NumericDomain&) noexcept(
      (std::is_nothrow_copy_constructible< UninitializedDomain >::value) &&
      (std::is_nothrow_copy_constructible< NumericDomainT >::value)) =
      default;

  /// \brief Move constructor
  NumericDomain(NumericDomain&&) noexcept(
      (std::is_nothrow_move_constructible< UninitializedDomain >::value) &&
      (std::is_nothrow_move_constructible< NumericDomainT >::value)) =
      default;

  /// \brief Copy assignment operator
  NumericDomain& operator=(const NumericDomain&) noexcept(
      (std::is_nothrow_copy_assignable< UninitializedDomain >::value) &&
      (std::is_nothrow_copy_assignable< NumericDomainT >::value)) = default;

  /// \brief Move assignment operator
  NumericDomain& operator=(NumericDomain&&) noexcept(
      (std::is_nothrow_move_assignable< UninitializedDomain >::value) &&
      (std::is_nothrow_move_assignable< NumericDomainT >::value)) = default;

  /// \brief Destructor
  ~NumericDomain() override = default;

  /// \name Implement core abstract domain methods
  /// @{

  void normalize() override {
    this->_uninitialized.normalize();
    if (this->_uninitialized.is_bottom()) {
      this->_numeric.set_to_bottom();
      return;
    }

    this->_numeric.normalize();
    if (this->_numeric.is_bottom()) {
      this->_uninitialized.set_to_bottom();
      return;
    }
  }

private:
  /// \brief Return true if the abstract value is bottom
  ///
  /// This is not always correct since it doesn't check this->_numeric
  bool is_bottom_fast() const { return this->_uninitialized.is_bottom(); }

public:
  bool is_bottom() const override {
    return this->_uninitialized.is_bottom() || this->_numeric.is_bottom();
  }

  bool is_top() const override {
    return this->_uninitialized.is_top() && this->_numeric.is_top();
  }

  void set_to_bottom() override {
    this->_uninitialized.set_to_bottom();
    this->_numeric.set_to_bottom();
  }

  void set_to_top() override {
    this->_uninitialized.set_to_top();
    this->_numeric.set_to_top();
  }

  bool leq(const NumericDomain& other) const override {
    if (this->is_bottom()) {
      return true;
    } else if (other.is_bottom()) {
      return false;
    } else {
      return this->_uninitialized.leq(other._uninitialized) &&
             this->_numeric.leq(other._numeric);
    }
  }

  bool equals(const NumericDomain& other) const override {
    if (this->is_bottom()) {
      return other.is_bottom();
    } else if (other.is_bottom()) {
      return false;
    } else {
      return this->_uninitialized.equals(other._uninitialized) &&
             this->_numeric.equals(other._numeric);
    }
  }

  void join_with(NumericDomain&& other) override {
    this->normalize();
    other.normalize();
    if (this->is_bottom()) {
      this->operator=(std::move(other));
    } else if (other.is_bottom()) {
      return;
    } else {
      this->_uninitialized.join_with(std::move(other._uninitialized));
      this->_numeric.join_with(std::move(other._numeric));
    }
  }

  void join_with(const NumericDomain& other) override {
    this->normalize();
    if (this->is_bottom()) {
      this->operator=(other);
    } else if (other.is_bottom()) {
      return;
    } else {
      this->_uninitialized.join_with(other._uninitialized);
      this->_numeric.join_with(other._numeric);
    }
  }

  void join_loop_with(NumericDomain&& other) override {
    this->normalize();
    other.normalize();
    if (this->is_bottom()) {
      this->operator=(std::move(other));
    } else if (other.is_bottom()) {
      return;
    } else {
      this->_uninitialized.join_loop_with(std::move(other._uninitialized));
      this->_numeric.join_loop_with(std::move(other._numeric));
    }
  }

  void join_loop_with(const NumericDomain& other) override {
    this->normalize();
    if (this->is_bottom()) {
      this->operator=(other);
    } else if (other.is_bottom()) {
      return;
    } else {
      this->_uninitialized.join_loop_with(other._uninitialized);
      this->_numeric.join_loop_with(other._numeric);
    }
  }

  void join_iter_with(NumericDomain&& other) override {
    this->normalize();
    other.normalize();
    if (this->is_bottom()) {
      this->operator=(std::move(other));
    } else if (other.is_bottom()) {
      return;
    } else {
      this->_uninitialized.join_iter_with(std::move(other._uninitialized));
      this->_numeric.join_iter_with(std::move(other._numeric));
    }
  }

  void join_iter_with(const NumericDomain& other) override {
    this->normalize();
    if (this->is_bottom()) {
      this->operator=(other);
    } else if (other.is_bottom()) {
      return;
    } else {
      this->_uninitialized.join_iter_with(other._uninitialized);
      this->_numeric.join_iter_with(other._numeric);
    }
  }

  void widen_with(const NumericDomain& other) override {
    this->normalize();
    if (this->is_bottom()) {
      this->operator=(other);
    } else if (other.is_bottom()) {
      return;
    } else {
      this->_uninitialized.widen_with(other._uninitialized);
      this->_numeric.widen_with(other._numeric);
    }
  }

  void widen_threshold_with(const NumericDomain& other,
                            const FNumber& threshold) override {
    this->normalize();
    if (this->is_bottom()) {
      this->operator=(other);
    } else if (other.is_bottom()) {
      return;
    } else {
      this->_uninitialized.widen_with(other._uninitialized);
      this->_numeric.widen_threshold_with(other._numeric, threshold);
    }
  }

  void meet_with(const NumericDomain& other) override {
    this->normalize();
    if (this->is_bottom()) {
      return;
    } else if (other.is_bottom()) {
      this->set_to_bottom();
    } else {
      this->_uninitialized.meet_with(other._uninitialized);
      this->_numeric.meet_with(other._numeric);
    }
  }

  void narrow_with(const NumericDomain& other) override {
    this->normalize();
    if (this->is_bottom()) {
      return;
    } else if (other.is_bottom()) {
      this->set_to_bottom();
    } else {
      this->_uninitialized.narrow_with(other._uninitialized);
      this->_numeric.narrow_with(other._numeric);
    }
  }

  void narrow_threshold_with(const NumericDomain& other,
                             const MachineInt& threshold) override {
    this->normalize();
    if (this->is_bottom()) {
      return;
    } else if (other.is_bottom()) {
      this->set_to_bottom();
    } else {
      this->_uninitialized.narrow_with(other._uninitialized);
      this->_numeric.narrow_threshold_with(other._numeric, threshold);
    }
  }

  NumericDomain join(const NumericDomain& other) const override {
    if (this->is_bottom()) {
      return other;
    } else if (other.is_bottom()) {
      return *this;
    } else {
      return NumericDomain(this->_uninitialized.join(other._uninitialized),
                              this->_numeric.join(other._numeric));
    }
  }

  NumericDomain join_loop(const NumericDomain& other) const override {
    if (this->is_bottom()) {
      return other;
    } else if (other.is_bottom()) {
      return *this;
    } else {
      return NumericDomain(this->_uninitialized.join_loop(
                                  other._uninitialized),
                              this->_numeric.join_loop(other._numeric));
    }
  }

  NumericDomain join_iter(const NumericDomain& other) const override {
    if (this->is_bottom()) {
      return other;
    } else if (other.is_bottom()) {
      return *this;
    } else {
      return NumericDomain(this->_uninitialized.join_iter(
                                  other._uninitialized),
                              this->_numeric.join_iter(other._numeric));
    }
  }

  NumericDomain widening(const NumericDomain& other) const override {
    if (this->is_bottom()) {
      return other;
    } else if (other.is_bottom()) {
      return *this;
    } else {
      return NumericDomain(this->_uninitialized.widening(
                                  other._uninitialized),
                              this->_numeric.widening(other._numeric));
    }
  }

  NumericDomain widening_threshold(
      const NumericDomain& other,
      const FNumber& threshold) const override {
    if (this->is_bottom()) {
      return other;
    } else if (other.is_bottom()) {
      return *this;
    } else {
      return NumericDomain(this->_uninitialized.widening(
                                  other._uninitialized),
                              this->_numeric.widening_threshold(other._numeric,
                                                                threshold));
    }
  }

  NumericDomain meet(const NumericDomain& other) const override {
    if (this->is_bottom()) {
      return *this;
    } else if (other.is_bottom()) {
      return other;
    } else {
      return NumericDomain(this->_uninitialized.meet(other._uninitialized),
                              this->_numeric.meet(other._numeric));
    }
  }

  NumericDomain narrowing(const NumericDomain& other) const override {
    if (this->is_bottom()) {
      return *this;
    } else if (other.is_bottom()) {
      return other;
    } else {
      return NumericDomain(this->_uninitialized.narrowing(
                                  other._uninitialized),
                              this->_numeric.narrowing(other._numeric));
    }
  }

  NumericDomain narrowing_threshold(
      const NumericDomain& other,
      const FNumber& threshold) const override {
    if (this->is_bottom()) {
      return *this;
    } else if (other.is_bottom()) {
      return other;
    } else {
      return NumericDomain(this->_uninitialized.narrowing(
                                  other._uninitialized),
                              this->_numeric.narrowing_threshold(other._numeric,
                                                                 threshold));
    }
  }

  /// @}
  /// \name Implement uninitialized abstract domain methods
  /// @{

  void uninit_assert_initialized(VariableRef x) override {
    this->_uninitialized.assert_initialized(x);
  }

  bool uninit_is_initialized(VariableRef x) const override {
    return this->_uninitialized.is_initialized(x);
  }

  bool uninit_is_uninitialized(VariableRef x) const override {
    return this->_uninitialized.is_uninitialized(x);
  }

  void uninit_refine(VariableRef x, Uninitialized value) override {
    this->_uninitialized.refine(x, value);
  }

  Uninitialized uninit_to_uninitialized(VariableRef x) const override {
    return this->_uninitialized.get(x);
  }

  /// @}
  /// \name Implement machine integer abstract domain methods
  /// @{

  void float_assign(VariableRef x, const FNumber& n) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.assign(x, n);
  }

  void float_assign_undef(VariableRef x) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_uninitialized(x);
    this->_numeric.forget(x);
  }

  void float_assign_nondet(VariableRef x) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.forget(x);
  }

  void float_assign(VariableRef x, VariableRef y) override {
    ikos_assert(ScalarVariableTrait::is_float(x));
    ikos_assert(ScalarVariableTrait::is_float(y));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign(x, y);
    this->_numeric.assign(x, y);
  }

  void float_assign(VariableRef x, const FnuLinearExpression& e) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    if (this->is_bottom_fast()) {
      return;
    }

    for (const auto& term : e) {
      ikos_assert(ScalarVariableTrait::is_float(term.first));
      this->_uninitialized.assert_initialized(term.first);
    }

    if (this->_uninitialized.is_bottom()) {
      this->set_to_bottom();
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.assign(x, e);
  }

/*
  void float_apply(FnuUnaryOperator op, VariableRef x, VariableRef y) override {
    ikos_assert(ScalarVariableTrait::is_float(x));
    ikos_assert(ScalarVariableTrait::is_float(y));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(y);

    if (this->_uninitialized.is_bottom()) {
      this->set_to_bottom();
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.apply(op, x, y);
  }
*/

  void float_apply(FnuBinaryOperator op,
                 VariableRef x,
                 VariableRef y,
                 VariableRef z) override {
    ikos_assert(ScalarVariableTrait::is_float(x));
    ikos_assert(ScalarVariableTrait::is_float(y));
    ikos_assert(ScalarVariableTrait::is_float(z));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(y);
    this->_uninitialized.assert_initialized(z);

    if (this->_uninitialized.is_bottom()) {
      this->set_to_bottom();
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.apply(op, x, y, z);
  }

  void float_apply(FnuBinaryOperator op,
                 VariableRef x,
                 VariableRef y,
                 const FNumber& z) override {
    ikos_assert(ScalarVariableTrait::is_float(x));
    ikos_assert(ScalarVariableTrait::is_float(y));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(y);

    if (this->_uninitialized.is_bottom()) {
      this->set_to_bottom();
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.apply(op, x, y, z);
  }

  void float_apply(FnuBinaryOperator op,
                 VariableRef x,
                 const FNumber& y,
                 VariableRef z) override {
    ikos_assert(ScalarVariableTrait::is_float(x));
    ikos_assert(ScalarVariableTrait::is_float(z));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(z);

    if (this->_uninitialized.is_bottom()) {
      this->set_to_bottom();
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.apply(op, x, y, z);
  }

  void float_add(FnuPredicate pred, VariableRef x, VariableRef y) override {
    ikos_assert(ScalarVariableTrait::is_float(x));
    ikos_assert(ScalarVariableTrait::is_float(y));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(x);
    this->_uninitialized.assert_initialized(y);

    if (this->_uninitialized.is_bottom()) {
      this->set_to_bottom();
      return;
    }

    this->_numeric.add(pred, x, y);
  }

  void float_add(FnuPredicate pred, VariableRef x, const FNumber& y) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(x);

    if (this->_uninitialized.is_bottom()) {
      this->set_to_bottom();
      return;
    }

    this->_numeric.add(pred, x, y);
  }

  void float_add(FnuPredicate pred, const FNumber& x, VariableRef y) override {
    ikos_assert(ScalarVariableTrait::is_float(y));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(y);

    if (this->_uninitialized.is_bottom()) {
      this->set_to_bottom();
      return;
    }

    this->_numeric.add(pred, x, y);
  }

  void float_set(VariableRef x, const FnuInterval& value) override {
    ikos_assert(ScalarVariableTrait::is_int(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.set(x, value);
  }

  void float_set(VariableRef x, const FnuCongruence& value) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.set(x, value);
  }

  void float_set(VariableRef x, const FnuIntervalCongruence& value) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.set(x, value);
  }

  void float_refine(VariableRef x, const FnuInterval& value) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    this->_numeric.refine(x, value);
  }

  void float_refine(VariableRef x, const FnuCongruence& value) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    this->_numeric.refine(x, value);
  }

  void float_refine(VariableRef x, const FnuIntervalCongruence& value) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    this->_numeric.refine(x, value);
  }

  void float_forget(VariableRef x) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.forget(x);
    this->_numeric.forget(x);
  }

  FnuInterval float_to_interval(VariableRef x) const override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    return this->_numeric.to_interval(x);
  }

  FnuInterval float_to_interval(const FnuLinearExpression& e) const override {
    return this->_numeric.to_interval(e);
  }

  FnuCongruence float_to_congruence(VariableRef x) const override {
    ikos_assert(ScalarVariableTrait::is_int(x));

    return this->_numeric.to_congruence(x);
  }

  FnuCongruence float_to_congruence(const FnuLinearExpression& e) const override {
    return this->_numeric.to_congruence(e);
  }

  FnuIntervalCongruence float_to_interval_congruence(
      VariableRef x) const override {
    ikos_assert(ScalarVariableTrait::is_int(x));

    return this->_numeric.to_interval_congruence(x);
  }

  FnuIntervalCongruence float_to_interval_congruence(
      const FnuLinearExpression& e) const override {
    return this->_numeric.to_interval_congruence(e);
  }

  /// @}
  /// \name Implement non-negative loop counter abstract domain methods
  /// @{

  void counter_mark(VariableRef x) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    this->_numeric.counter_mark(x);
  }

  void counter_unmark(VariableRef x) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    this->_numeric.counter_unmark(x);
  }

  void counter_init(VariableRef x, const FNumber& c) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    this->_numeric.counter_init(x, c);
  }

  void counter_incr(VariableRef x, const FNumber& k) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    this->_numeric.counter_incr(x, k);
  }

  void counter_forget(VariableRef x) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    this->_numeric.counter_forget(x);
  }

  /// @}
  /// \name Implement floating point abstract domain methods
  /// @{

  /// \todo(floating point)
  /*  void float_assign_undef(VariableRef x) override {
      ikos_assert(ScalarVariableTrait::is_float(x));

      this->_uninitialized.assign_uninitialized(x);
    }

    void float_assign_nondet(VariableRef x) override {
      ikos_assert(ScalarVariableTrait::is_float(x));

      this->_uninitialized.assign_initialized(x);
    }

    void float_assign(VariableRef x, VariableRef y) override {
      ikos_assert(ScalarVariableTrait::is_float(x));
      ikos_assert(ScalarVariableTrait::is_float(y));

      this->_uninitialized.assign(x, y);
    }

    void float_forget(VariableRef x) override {
      ikos_assert(ScalarVariableTrait::is_float(x));

      this->_uninitialized.forget(x);
    }*/

  void float_assign(VariableRef x, const FNumber& n) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.assign(x, n);
  }

  void float_assign_undef(VariableRef x) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_uninitialized(x);
    this->_numeric.forget(x);
  }

  void float_assign_nondet(VariableRef x) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.forget(x);
  }

  void float_assign(VariableRef x, VariableRef y) override {
    ikos_assert(ScalarVariableTrait::is_float(x));
    ikos_assert(ScalarVariableTrait::is_float(y));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign(x, y);
    this->_numeric.assign(x, y);
  }

  void float_assign(VariableRef x, const FnuLinearExpression& e) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    if (this->is_bottom_fast()) {
      return;
    }

    for (const auto& term : e) {
      ikos_assert(ScalarVariableTrait::is_float(term.first));
      this->_uninitialized.assert_initialized(term.first);
    }

    if (this->_uninitialized.is_bottom()) {
      this->set_to_bottom();
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.assign(x, e);
  }

  /*  void float_apply(FnuUnaryOperator op, VariableRef x, VariableRef y)
    override{

    }*/

  void float_apply(FnuBinaryOperator op,
                   VariableRef x,
                   VariableRef y,
                   VariableRef z) override {
    ikos_assert(ScalarVariableTrait::is_float(x));
    ikos_assert(ScalarVariableTrait::is_float(y));
    ikos_assert(ScalarVariableTrait::is_float(z));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(y);
    this->_uninitialized.assert_initialized(z);

    if (this->_uninitialized.is_bottom()) {
      this->set_to_bottom();
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.apply(op, x, y, z);
  }

  void float_apply(FnuBinaryOperator op,
                   VariableRef x,
                   VariableRef y,
                   const FNumber& z) override {
    ikos_assert(ScalarVariableTrait::is_float(x));
    ikos_assert(ScalarVariableTrait::is_float(y));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(y);

    if (this->_uninitialized.is_bottom()) {
      this->set_to_bottom();
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.apply(op, x, y, z);
  }

  void float_apply(FnuBinaryOperator op,
                   VariableRef x,
                   const FNumber& y,
                   VariableRef z) override {
    ikos_assert(ScalarVariableTrait::is_float(x));
    ikos_assert(ScalarVariableTrait::is_float(z));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(z);

    if (this->_uninitialized.is_bottom()) {
      this->set_to_bottom();
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.apply(op, x, y, z);
  }

  void float_add(FnuPredicate pred, VariableRef x, VariableRef y) override {
    ikos_assert(ScalarVariableTrait::is_float(x));
    ikos_assert(ScalarVariableTrait::is_float(y));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(x);
    this->_uninitialized.assert_initialized(y);

    if (this->_uninitialized.is_bottom()) {
      this->set_to_bottom();
      return;
    }

    this->_numeric.add(pred, x, y);
  }

  void float_add(FnuPredicate pred, VariableRef x, const FNumber& y) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(x);

    if (this->_uninitialized.is_bottom()) {
      this->set_to_bottom();
      return;
    }

    this->_numeric.add(pred, x, y);
  }

  void float_add(FnuPredicate pred, const FNumber& x, VariableRef y) override {
    ikos_assert(ScalarVariableTrait::is_float(y));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(y);

    if (this->_uninitialized.is_bottom()) {
      this->set_to_bottom();
      return;
    }

    this->_numeric.add(pred, x, y);
  }

  void float_set(VariableRef x, const FnuInterval& value) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.set(x, value);
  }

  void float_set(VariableRef x, const FnuCongruence& value) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.set(x, value);
  }

  void float_set(VariableRef x, const FnuIntervalCongruence& value) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.set(x, value);
  }

  void float_refine(VariableRef x, const FnuInterval& value) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    this->_numeric.refine(x, value);
  }

  void float_refine(VariableRef x, const FnuCongruence& value) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    this->_numeric.refine(x, value);
  }

  void float_refine(VariableRef x,
                    const FnuIntervalCongruence& value) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    this->_numeric.refine(x, value);
  }

  void float_forget(VariableRef x) override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.forget(x);
    this->_numeric.forget(x);
  }

  FnuInterval float_to_interval(VariableRef x) const override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    return this->_numeric.to_interval(x);
  }

  FnuInterval float_to_interval(const FnuLinearExpression& e) const override {
    return this->_numeric.to_interval(e);
  }

  FnuCongruence float_to_congruence(VariableRef x) const override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    return this->_numeric.to_congruence(x);
  }

  FnuCongruence float_to_congruence(
      const FnuLinearExpression& e) const override {
    return this->_numeric.to_congruence(e);
  }

  FnuIntervalCongruence float_to_interval_congruence(
      VariableRef x) const override {
    ikos_assert(ScalarVariableTrait::is_float(x));

    return this->_numeric.to_interval_congruence(x);
  }

  FnuIntervalCongruence float_to_interval_congruence(
      const FnuLinearExpression& e) const override {
    return this->_numeric.to_interval_congruence(e);
  }

  /// @}
  /// \name Implement nullity abstract domain methods
  /// @{

  void nullity_assert_null(VariableRef p) override {
    ikos_assert(ScalarVariableTrait::is_pointer(p));

    this->_uninitialized.assert_initialized(p);
  }

  void nullity_assert_non_null(VariableRef p) override {
    ikos_assert(ScalarVariableTrait::is_pointer(p));

    this->_uninitialized.assert_initialized(p);
  }

  bool nullity_is_null(VariableRef) const override { return this->is_bottom(); }

  bool nullity_is_non_null(VariableRef) const override {
    return this->is_bottom();
  }

  void nullity_set(VariableRef, Nullity value) override {
    if (value.is_bottom()) {
      this->set_to_bottom();
    }
  }

  void nullity_refine(VariableRef, Nullity value) override {
    if (value.is_bottom()) {
      this->set_to_bottom();
    }
  }

  Nullity nullity_to_nullity(VariableRef) const override {
    if (this->is_bottom()) {
      return Nullity::bottom();
    } else {
      return Nullity::top();
    }
  }

  /// @}
  /// \name Implement pointer abstract domain methods
  /// @{

  void pointer_assign(VariableRef p, MemoryLocationRef, Nullity) override {
    ikos_assert(ScalarVariableTrait::is_pointer(p));

    this->_uninitialized.assign_initialized(p);
  }

  void pointer_assign_null(VariableRef p) override {
    ikos_assert(ScalarVariableTrait::is_pointer(p));

    this->_uninitialized.assign_initialized(p);
  }

  void pointer_assign_undef(VariableRef p) override {
    ikos_assert(ScalarVariableTrait::is_pointer(p));

    this->_uninitialized.assign_uninitialized(p);
  }

  void pointer_assign_nondet(VariableRef p) override {
    ikos_assert(ScalarVariableTrait::is_pointer(p));

    this->_uninitialized.assign_initialized(p);
  }

  void pointer_assign(VariableRef p, VariableRef q) override {
    ikos_assert(ScalarVariableTrait::is_pointer(p));
    ikos_assert(ScalarVariableTrait::is_pointer(q));

    this->_uninitialized.assign(p, q);
  }

  void pointer_assign(VariableRef p, VariableRef q, VariableRef o) override {
    ikos_assert(ScalarVariableTrait::is_pointer(p));
    ikos_assert(ScalarVariableTrait::is_pointer(q));
    ikos_assert(ScalarVariableTrait::is_int(o));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(q);
    this->_uninitialized.assert_initialized(o);
    this->_uninitialized.assign_initialized(p);
  }

  void pointer_assign(VariableRef p,
                      VariableRef q,
                      const MachineInt&) override {
    ikos_assert(ScalarVariableTrait::is_pointer(p));
    ikos_assert(ScalarVariableTrait::is_pointer(q));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(q);
    this->_uninitialized.assign_initialized(p);
  }

  void pointer_assign(VariableRef p,
                      VariableRef q,
                      const IntLinearExpression& o) override {
    ikos_assert(ScalarVariableTrait::is_pointer(p));
    ikos_assert(ScalarVariableTrait::is_pointer(q));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(q);
    for (const auto& term : o) {
      ikos_assert(ScalarVariableTrait::is_int(term.first));
      this->_uninitialized.assert_initialized(term.first);
    }

    this->_uninitialized.assign_initialized(p);
  }

  void pointer_add(PointerPredicate, VariableRef p, VariableRef q) override {
    ikos_assert(ScalarVariableTrait::is_pointer(p));
    ikos_assert(ScalarVariableTrait::is_pointer(q));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(p);
    this->_uninitialized.assert_initialized(q);
  }

  void pointer_refine(VariableRef, const PointsToSetT& addrs) override {
    if (addrs.is_bottom()) {
      this->set_to_bottom();
    }
  }

  void pointer_refine(VariableRef,
                      const PointsToSetT& addrs,
                      const IntInterval& offset) override {
    if (addrs.is_bottom() || offset.is_bottom()) {
      this->set_to_bottom();
    }
  }

  void pointer_refine(VariableRef, const PointerAbsValueT& value) override {
    if (value.is_bottom()) {
      this->set_to_bottom();
    }
  }

  void pointer_refine(VariableRef, const PointerSetT& set) override {
    if (set.is_bottom()) {
      this->set_to_bottom();
    }
  }

  void pointer_offset_to_int(VariableRef x, VariableRef p) override {
    ikos_assert(ScalarVariableTrait::is_int(x));
    ikos_assert(ScalarVariableTrait::is_pointer(p));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(p);
    this->_uninitialized.assign_initialized(x);
    this->_numeric.forget(x);
  }

  IntInterval pointer_offset_to_interval(VariableRef p) const override {
    ikos_assert(ScalarVariableTrait::is_pointer(p));

    auto o = ScalarVariableTrait::offset_var(p);
    if (this->is_bottom()) {
      return IntInterval::bottom(IntVariableTrait::bit_width(o),
                                 IntVariableTrait::sign(o));
    } else {
      return IntInterval::top(IntVariableTrait::bit_width(o),
                              IntVariableTrait::sign(o));
    }
  }

  IntCongruence pointer_offset_to_congruence(VariableRef p) const override {
    ikos_assert(ScalarVariableTrait::is_pointer(p));

    auto o = ScalarVariableTrait::offset_var(p);
    if (this->is_bottom()) {
      return IntCongruence::bottom(IntVariableTrait::bit_width(o),
                                   IntVariableTrait::sign(o));
    } else {
      return IntCongruence::top(IntVariableTrait::bit_width(o),
                                IntVariableTrait::sign(o));
    }
  }

  IntIntervalCongruence pointer_offset_to_interval_congruence(
      VariableRef p) const override {
    ikos_assert(ScalarVariableTrait::is_pointer(p));

    auto o = ScalarVariableTrait::offset_var(p);
    if (this->is_bottom()) {
      return IntIntervalCongruence::bottom(IntVariableTrait::bit_width(o),
                                           IntVariableTrait::sign(o));
    } else {
      return IntIntervalCongruence::top(IntVariableTrait::bit_width(o),
                                        IntVariableTrait::sign(o));
    }
  }

  PointsToSetT pointer_to_points_to(VariableRef) const override {
    if (this->is_bottom()) {
      return PointsToSetT::bottom();
    } else {
      return PointsToSetT::top();
    }
  }

  PointerAbsValueT pointer_to_pointer(VariableRef p) const override {
    ikos_assert(ScalarVariableTrait::is_pointer(p));

    auto o = ScalarVariableTrait::offset_var(p);
    if (this->is_bottom()) {
      return PointerAbsValueT::bottom(IntVariableTrait::bit_width(o),
                                      IntVariableTrait::sign(o));
    } else {
      return PointerAbsValueT::top(IntVariableTrait::bit_width(o),
                                   IntVariableTrait::sign(o));
    }
  }

  void pointer_forget_offset(VariableRef) override {}

  void pointer_forget(VariableRef p) override {
    ikos_assert(ScalarVariableTrait::is_pointer(p));

    this->_uninitialized.forget(p);
  }

  /// @}
  /// \name Implement dynamically typed variables abstract domain methods
  /// @{

  void dynamic_assign(VariableRef x, VariableRef y) override {
    ikos_assert(ScalarVariableTrait::is_dynamic(x));
    ikos_assert(ScalarVariableTrait::is_dynamic(y));
    ikos_assert(IntVariableTrait::bit_width(x) ==
                IntVariableTrait::bit_width(y));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign(x, y);
    if (IntVariableTrait::sign(x) == IntVariableTrait::sign(y)) {
      this->_numeric.assign(x, y);
    } else {
      this->_numeric.apply(IntUnaryOperator::SignCast, x, y);
    }
  }

  void dynamic_write_undef(VariableRef x) override {
    ikos_assert(ScalarVariableTrait::is_dynamic(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_uninitialized(x);
    this->_numeric.forget(x);
  }

  void dynamic_write_nondet(VariableRef x) override {
    ikos_assert(ScalarVariableTrait::is_dynamic(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.forget(x);
  }

  void dynamic_write_int(VariableRef x, const MachineInt& n) override {
    ikos_assert(ScalarVariableTrait::is_dynamic(x));
    ikos_assert(IntVariableTrait::bit_width(x) == n.bit_width());

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_initialized(x);
    if (IntVariableTrait::sign(x) == n.sign()) {
      this->_numeric.assign(x, n);
    } else {
      this->_numeric.assign(x, n.sign_cast(IntVariableTrait::sign(x)));
    }
  }

  void dynamic_write_nondet_int(VariableRef x) override {
    ikos_assert(ScalarVariableTrait::is_dynamic(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.forget(x);
  }

  void dynamic_write_int(VariableRef x, VariableRef y) override {
    ikos_assert(ScalarVariableTrait::is_dynamic(x));
    ikos_assert(ScalarVariableTrait::is_int(y));
    ikos_assert(IntVariableTrait::bit_width(x) ==
                IntVariableTrait::bit_width(y));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign(x, y);
    if (IntVariableTrait::sign(x) == IntVariableTrait::sign(y)) {
      this->_numeric.assign(x, y);
    } else {
      this->_numeric.apply(IntUnaryOperator::SignCast, x, y);
    }
  }

  void dynamic_write_nondet_float(VariableRef x) override {
    ikos_assert(ScalarVariableTrait::is_dynamic(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.forget(x);
  }

  void dynamic_write_null(VariableRef x) override {
    ikos_assert(ScalarVariableTrait::is_dynamic(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.forget(x);
  }

  void dynamic_write_pointer(VariableRef x,
                             MemoryLocationRef,
                             Nullity) override {
    ikos_assert(ScalarVariableTrait::is_dynamic(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign_initialized(x);
    this->_numeric.forget(x);
  }

  void dynamic_write_pointer(VariableRef x, VariableRef y) override {
    ikos_assert(ScalarVariableTrait::is_dynamic(x));
    ikos_assert(ScalarVariableTrait::is_pointer(y));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign(x, y);
    this->_numeric.forget(x);
  }

  void dynamic_read_int(VariableRef x, VariableRef y) override {
    ikos_assert(ScalarVariableTrait::is_int(x));
    ikos_assert(ScalarVariableTrait::is_dynamic(y));
    ikos_assert(IntVariableTrait::bit_width(x) ==
                IntVariableTrait::bit_width(y));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assign(x, y);
    if (IntVariableTrait::sign(x) == IntVariableTrait::sign(y)) {
      this->_numeric.assign(x, y);
    } else {
      this->_numeric.apply(IntUnaryOperator::SignCast, x, y);
    }
  }

  void dynamic_read_pointer(VariableRef x, VariableRef y) override {
    ikos_assert(ScalarVariableTrait::is_pointer(x));
    ikos_assert(ScalarVariableTrait::is_dynamic(y));

    this->_uninitialized.assign(x, y);
  }

  bool dynamic_is_zero(VariableRef x) const override {
    ikos_assert(ScalarVariableTrait::is_dynamic(x));

    IntInterval value = this->_numeric.to_interval(x);
    return value.is_bottom() || value.is_zero();
  }

  bool dynamic_is_null(VariableRef x) const override {
    ikos_assert(ScalarVariableTrait::is_dynamic(x));
    ikos_ignore(x);

    return this->is_bottom();
  }

  void dynamic_forget(VariableRef x) override {
    ikos_assert(ScalarVariableTrait::is_dynamic(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.forget(x);
    this->_numeric.forget(x);
  }

  /// @}
  /// \name Implement scalar abstract domain methods
  /// @{

  void scalar_assign_undef(VariableRef x) override {
    if (this->is_bottom_fast()) {
      return;
    } else if (ScalarVariableTrait::is_int(x)) {
      this->int_assign_undef(x);
    } else if (ScalarVariableTrait::is_float(x)) {
      this->float_assign_undef(x);
    } else if (ScalarVariableTrait::is_pointer(x)) {
      this->pointer_assign_undef(x);
    } else if (ScalarVariableTrait::is_dynamic(x)) {
      this->dynamic_write_undef(x);
    } else {
      ikos_unreachable("unexpected type");
    }
  }

  void scalar_assign_nondet(VariableRef x) override {
    if (this->is_bottom_fast()) {
      return;
    } else if (ScalarVariableTrait::is_int(x)) {
      this->int_assign_nondet(x);
    } else if (ScalarVariableTrait::is_float(x)) {
      this->float_assign_nondet(x);
    } else if (ScalarVariableTrait::is_pointer(x)) {
      this->pointer_assign_nondet(x);
    } else if (ScalarVariableTrait::is_dynamic(x)) {
      this->dynamic_write_nondet(x);
    } else {
      ikos_unreachable("unexpected type");
    }
  }

  void scalar_float_to_int(VariableRef f, VariableRef x) override {
    ikos_assert(ScalarVariableTrait::is_int(x));
    ikos_assert(ScalarVariableTrait::is_float(f));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(f);
    this->_uninitialized.assign_initialized(x);
    this->_numeric.forget(x);
  }

  void scalar_int_to_float(VariableRef x, VariableRef f) override {
    ikos_assert(ScalarVariableTrait::is_float(f));
    ikos_assert(ScalarVariableTrait::is_int(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(x);
    this->_uninitialized.assign_initialized(f);
  }

  /// \brief pointer -> integer
  void scalar_pointer_to_int(VariableRef x,
                             VariableRef p,
                             MemoryLocationRef) override {
    ikos_assert(ScalarVariableTrait::is_int(x));
    ikos_assert(ScalarVariableTrait::is_pointer(p));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(p);
    this->_uninitialized.assign_initialized(x);
    this->_numeric.forget(x);
  }

  void scalar_int_to_pointer(VariableRef p,
                             VariableRef x,
                             MemoryLocationRef) override {
    ikos_assert(ScalarVariableTrait::is_pointer(p));
    ikos_assert(ScalarVariableTrait::is_int(x));

    if (this->is_bottom_fast()) {
      return;
    }

    this->_uninitialized.assert_initialized(x);
    this->_uninitialized.assign_initialized(p);
  }

  void scalar_forget(VariableRef x) override {
    if (this->is_bottom_fast()) {
      return;
    } else if (ScalarVariableTrait::is_int(x)) {
      this->int_forget(x);
    } else if (ScalarVariableTrait::is_float(x)) {
      this->float_forget(x);
    } else if (ScalarVariableTrait::is_pointer(x)) {
      this->pointer_forget(x);
    } else if (ScalarVariableTrait::is_dynamic(x)) {
      this->dynamic_forget(x);
    } else {
      ikos_unreachable("unexpected type");
    }
  }

  /// @}

  void dump(std::ostream& o) const override {
    if (this->is_bottom()) {
      o << "⊥";
    } else {
      o << "(";
      this->_uninitialized.dump(o);
      o << ", ";
      this->_numeric.dump(o);
      o << ")";
    }
  }

  static std::string name() {
    return "machine integer scalar domain using " +
           UninitializedDomain::name() + " and " + NumericDomainT::name();
  }

}; // end class MachineIntDomain

} // end namespace scalar
} // end namespace core
} // end namespace ikos
