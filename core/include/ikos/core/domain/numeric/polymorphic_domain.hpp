//
// Created by zoush99 on 1/11/24.
//

/*******************************************************************************
 *
 * \file
 * \brief Polymorphic floating point abstract domain
 *
 * The PolymorphicDomain is a floating point abstract domain whose behavior
 * depends on the abstract domain it is constructed with. It allows the use of
 * different abstract domains at runtime.
 *
 * Author: Maxime Arthaud
 *
 * Contact: ikos@lists.nasa.gov
 *
 * Notices:
 *
 * Copyright (c) 2018-2019 United States Government as represented by the
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
 * ERROR FREE, OR ANY WARRANTY THAT narrowing_thresholdDOCUMENTATION, IF
 *PROVIDED, WILL CONFORM TO THE SUBJECT SOFTWARE. THIS AGREEMENT DOES NOT, IN
 *ANY MANNER, CONSTITUTE AN ENDORSEMENT BY GOVERNMENT AGENCY OR ANY PRIOR
 *RECIPIENT OF ANY RESULTS, RESULTING DESIGNS, HARDWARE, SOFTWARE PRODUCTS OR
 *ANY OTHER APPLICATIONS RESULTING FROM USE OF THE SUBJECT SOFTWARE.  FURTHER,
 *GOVERNMENT AGENCY DISCLAIMS ALL WARRANTIES AND LIABILITIES REGARDING
 *THIRD-PARTY SOFTWARE, IF PRESENT IN THE ORIGINAL SOFTWARE, AND DISTRIBUTES IT
 *"AS IS."
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
#include <ikos/core/support/assert.hpp>
#include <ikos/core/support/mpl.hpp>
#include <memory>

namespace ikos {
namespace core {
namespace numeric {

/// \brief Polymorphic floating point abstract domain
///
/// The PolymorphicDomain is a floating point abstract domain whose behavior
/// depends on the abstract domain it is constructed with. It allows the use of
/// different abstract domains at runtime.
template < typename Number,
           typename VariableRef,
           std::size_t MaxReductionCycles = 10 >
class PolymorphicDomain final
    : public numeric::AbstractDomain<
          Number,
          VariableRef,
          PolymorphicDomain< Number, VariableRef, MaxReductionCycles > > {
public:
  using LinearExpressionT = LinearExpression< Number, VariableRef >;
  using LinearConstraintT =
      LinearConstraint< Number, VariableRef >; // By zoush99
  using LinearConstraintSystemT =
      LinearConstraintSystem< Number, VariableRef >; // By zoush99

private:
  /// Type erasure idiom
  ///
  /// This is commonly known as the 'type erasure idiom', used to implement
  /// std::any.

  class PolymorphicBase {
  public:
    /// \brief Default constructor
    PolymorphicBase() = default;

    /// \brief No copy constructor
    PolymorphicBase(const PolymorphicBase&) = delete;

    /// \brief No move constructor
    PolymorphicBase(PolymorphicBase&&) = delete;

    /// \brief No copy assignment operator
    PolymorphicBase& operator=(const PolymorphicBase&) = delete;

    /// \brief No move assignment operator
    PolymorphicBase& operator=(PolymorphicBase&&) = delete;

    /// \brief Destructor
    virtual ~PolymorphicBase() = default;

    /// \brief Clone the abstract value
    virtual std::unique_ptr< PolymorphicBase > clone() const = 0;

    /// \name Core abstract domain methods
    /// @{

    /// \brief Normalize the abstract value
    virtual void normalize() = 0;

    /// \brief Check if the abstract value is bottom
    virtual bool is_bottom() const = 0;

    /// \brief Check if the abstract value is top
    virtual bool is_top() const = 0;

    /// \brief Set the abstract value to bottom
    virtual void set_to_bottom() = 0;

    /// \brief Set the abstract value to top
    virtual void set_to_top() = 0;

    /// \brief Partial order comparison
    virtual bool leq(const PolymorphicBase& other) const = 0;

    /// \brief Equality comparison
    virtual bool equals(const PolymorphicBase& other) const = 0;

    /// \brief Perform the union of two abstract values
    virtual void join_with(PolymorphicBase&& other) = 0;

    /// \brief Perform the union of two abstract values
    virtual void join_with(const PolymorphicBase& other) = 0;

    /// \brief Perform a union on a loop head
    virtual void join_loop_with(PolymorphicBase&& other) = 0;

    /// \brief Perform a union on a loop head
    virtual void join_loop_with(const PolymorphicBase& other) = 0;

    /// \brief Perform a union on two consecutive iterations of a fix-point
    /// algorithm
    virtual void join_iter_with(PolymorphicBase&& other) = 0;

    /// \brief Perform a union on two consecutive iterations of a fix-point
    /// algorithm
    virtual void join_iter_with(const PolymorphicBase& other) = 0;

    /// \brief Perform the widening of two abstract values
    virtual void widen_with(const PolymorphicBase& other) = 0;

    /// \brief Perform the widening of two abstract values with a threshold
    virtual void widen_threshold_with(const PolymorphicBase& other,
                                      const Number& threshold) = 0;

    /// \brief Perform the intersection of two abstract values
    virtual void meet_with(const PolymorphicBase& other) = 0;

    /// \brief Perform the narrowing of two abstract values
    virtual void narrow_with(const PolymorphicBase& other) = 0;

    /// \brief Perform the narrowing of two abstract values with a threshold
    virtual void narrow_threshold_with(const PolymorphicBase& other,
                                       const Number& threshold) = 0;

    /// \brief Perform the union of two abstract values
    virtual std::unique_ptr< PolymorphicBase > join(
        const PolymorphicBase& other) const = 0;

    /// \brief Perform a union on a loop head
    virtual std::unique_ptr< PolymorphicBase > join_loop(
        const PolymorphicBase& other) const = 0;

    /// \brief Perform a union on two consecutive iterations of a fix-point
    /// algorithm
    virtual std::unique_ptr< PolymorphicBase > join_iter(
        const PolymorphicBase& other) const = 0;

    /// \brief Perform the widening of two abstract values
    virtual std::unique_ptr< PolymorphicBase > widening(
        const PolymorphicBase& other) const = 0;

    /// \brief Perform the widening of two abstract values with a threshold
    virtual std::unique_ptr< PolymorphicBase > widening_threshold(
        const PolymorphicBase& other, const Number& threshold) const = 0;

    /// \brief Perform the intersection of two abstract values
    virtual std::unique_ptr< PolymorphicBase > meet(
        const PolymorphicBase& other) const = 0;

    /// \brief Perform the narrowing of two abstract values
    virtual std::unique_ptr< PolymorphicBase > narrowing(
        const PolymorphicBase& other) const = 0;

    /// \brief Perform the narrowing of two abstract values with a threshold
    virtual std::unique_ptr< PolymorphicBase > narrowing_threshold(
        const PolymorphicBase& other, const Number& threshold) const = 0;

    /// @}
    /// \name Floating point abstract domain methods
    /// @{

    /// By zoush99
    /// \brief Assign `x = n`
    virtual void assign(VariableRef x, int n) = 0;

    /// \brief Assign `x = n`
    virtual void assign(VariableRef x, const Number& n) = 0;

    /// \brief Assign `x = y`
    virtual void assign(VariableRef x, VariableRef y) = 0;

    /// \brief Assign `x = e`
    virtual void assign(VariableRef x, const LinearExpressionT& e) = 0;

    /*
        /// \brief Apply `x = op y`
        virtual void apply(UnaryOperator op, VariableRef x, VariableRef y) = 0;
    */

    /// \brief Apply `x = y op z`
    virtual void apply(BinaryOperator op,
                       VariableRef x,
                       VariableRef y,
                       VariableRef z) = 0;

    /// \brief Apply `x = y op z`
    virtual void apply(BinaryOperator op,
                       VariableRef x,
                       VariableRef y,
                       const Number& z) = 0;

    /// \brief Apply `x = y op z`
    virtual void apply(BinaryOperator op,
                       VariableRef x,
                       const Number& y,
                       VariableRef z) = 0;

    /// By zoush99
    /// { @
    /// \brief Add a linear constraint
    virtual void add(const LinearConstraintT& cst) = 0;

    /// \brief Add a linear constraint system
    virtual void add(const LinearConstraintSystemT& csts) = 0;
    /// @ }

    /// \brief Add the constraint `x pred y`
    virtual void add(Predicate pred, VariableRef x, VariableRef y) = 0;

    /// \brief Add the constraint `x pred y`
    virtual void add(Predicate pred, VariableRef x, const Number& y) = 0;

    /// \brief Add the constraint `x pred y`
    virtual void add(Predicate pred, const Number& x, VariableRef y) = 0;

    /// \brief Set the interval value of a variable
    virtual void set(VariableRef x, const Interval< Number >& value) = 0;

    /// \brief Set the congruence value of a variable
    virtual void set(VariableRef x, const Congruence< Number >& value) = 0;

    /// \brief Set the interval-congruence value of a variable
    virtual void set(VariableRef x,
                     const IntervalCongruence< Number >& value) = 0;

    /// \brief Refine the value of a variable with an interval
    virtual void refine(VariableRef x, const Interval< Number >& value) = 0;

    /// \brief Refine the value of a variable with a congruence
    virtual void refine(VariableRef x, const Congruence< Number >& value) = 0;

    /// \brief Refine the value of a variable with an interval-congruence
    virtual void refine(VariableRef x,
                        const IntervalCongruence< Number >& value) = 0;

    /// \brief Forget a variable
    virtual void forget(VariableRef x) = 0;

    /// \brief Projection to an interval
    virtual Interval< Number > to_interval(VariableRef x) const = 0;

    /// \brief Projection to an interval
    virtual Interval< Number > to_interval(
        const LinearExpressionT& e) const = 0;

    /// \brief Projection to a congruence
    virtual Congruence< Number > to_congruence(VariableRef x) const = 0;

    /// \brief Projection to a congruence
    virtual Congruence< Number > to_congruence(
        const LinearExpressionT& e) const = 0;

    /// \brief Projection to an interval-congruence
    virtual IntervalCongruence< Number > to_interval_congruence(
        VariableRef x) const = 0;

    /// \brief Projection to an interval-congruence
    virtual IntervalCongruence< Number > to_interval_congruence(
        const LinearExpressionT& e) const = 0;

    /// \todo annotate
    virtual LinearConstraintSystemT to_linear_constraint_system() const =0;

    /// @}
    /// \name Non-negative loop counter abstract domain methods
    /// @{

    /// \brief Mark the variable `x` as a non-negative loop counter
    virtual void counter_mark(VariableRef x) = 0;

    /// \brief Mark the variable `x` as a normal variable, without losing
    /// information
    virtual void counter_unmark(VariableRef x) = 0;

    /// \brief Initialize a non-negative loop counter: `x = c`
    virtual void counter_init(VariableRef x, const Number& c) = 0;

    /// \brief Increment a non-negative loop counter counter: `x += k`
    virtual void counter_incr(VariableRef x, const Number& k) = 0;

    /// \brief Forget a non-negative loop counter
    virtual void counter_forget(VariableRef x) = 0;

    /// @}

    /// \brief Dump the abstract value, for debugging purpose
    virtual void dump(std::ostream&) const = 0;

  }; // end class PolymorphicBase

private:
  template < typename RuntimeDomain >
  class PolymorphicDerived final : public PolymorphicBase {
  public:
    static_assert(
        numeric::IsAbstractDomain< RuntimeDomain, Number, VariableRef >::value,
        "RuntimeDomain must implement Number::AbstractDomain");

  private:
    using PolymorphicDerivedT = PolymorphicDerived< RuntimeDomain >;

  private:
    /// \brief Specified abstract domain.
    RuntimeDomain _inv;

  public:
    /// \brief Create an abstract value
    explicit PolymorphicDerived(RuntimeDomain inv) : _inv(std::move(inv)) {}

    std::unique_ptr< PolymorphicBase > clone() const override {
      return std::make_unique< PolymorphicDerivedT >(this->_inv);
    }

    /// \name Core abstract domain methods
    /// @{

    void normalize() override { this->_inv.normalize(); }

    bool is_bottom() const override { return this->_inv.is_bottom(); }

    bool is_top() const override { return this->_inv.is_top(); }

    void set_to_bottom() override { this->_inv.set_to_bottom(); }

    void set_to_top() override { this->_inv.set_to_top(); }

    /// \brief Check if the parameter has the same runtime domain
    bool is_compatible(const PolymorphicBase& other) const {
      return dynamic_cast< const PolymorphicDerivedT* >(&other) != nullptr;
    }

    /// \brief Assert that the parameter has the same runtime domain
    void assert_compatible(const PolymorphicBase& other) const {
      ikos_assert_msg(this->is_compatible(other),
                      "incompatible runtime abstract domains");
      ikos_ignore(other);
    }

    bool leq(const PolymorphicBase& other) const override {
      this->assert_compatible(other);
      return this->_inv.leq(
          static_cast< const PolymorphicDerivedT& >(other)._inv);
    }

    bool equals(const PolymorphicBase& other) const override {
      this->assert_compatible(other);
      return this->_inv.equals(
          static_cast< const PolymorphicDerivedT& >(other)._inv);
    }

    void join_with(PolymorphicBase&& other) override {
      this->assert_compatible(other);
      this->_inv.join_with(
          std::move(static_cast< PolymorphicDerivedT& >(other)._inv));
    }

    void join_with(const PolymorphicBase& other) override {
      this->assert_compatible(other);
      this->_inv.join_with(
          static_cast< const PolymorphicDerivedT& >(other)._inv);
    }

    void join_loop_with(PolymorphicBase&& other) override {
      this->assert_compatible(other);
      this->_inv.join_loop_with(
          std::move(static_cast< PolymorphicDerivedT& >(other)._inv));
    }

    void join_loop_with(const PolymorphicBase& other) override {
      this->assert_compatible(other);
      this->_inv.join_loop_with(
          static_cast< const PolymorphicDerivedT& >(other)._inv);
    }

    void join_iter_with(PolymorphicBase&& other) override {
      this->assert_compatible(other);
      this->_inv.join_iter_with(
          std::move(static_cast< PolymorphicDerivedT& >(other)._inv));
    }

    void join_iter_with(const PolymorphicBase& other) override {
      this->assert_compatible(other);
      this->_inv.join_iter_with(
          static_cast< const PolymorphicDerivedT& >(other)._inv);
    }

    void widen_with(const PolymorphicBase& other) override {
      this->assert_compatible(other);
      this->_inv.widen_with(
          static_cast< const PolymorphicDerivedT& >(other)._inv);
    }

    void widen_threshold_with(const PolymorphicBase& other,
                              const Number& threshold) override {
      this->assert_compatible(other);
      this->_inv.widen_threshold_with(static_cast< const PolymorphicDerivedT& >(
                                          other)
                                          ._inv,
                                      threshold);
    }

    void meet_with(const PolymorphicBase& other) override {
      this->assert_compatible(other);
      this->_inv.meet_with(
          static_cast< const PolymorphicDerivedT& >(other)._inv);
    }

    void narrow_with(const PolymorphicBase& other) override {
      this->assert_compatible(other);
      this->_inv.narrow_with(
          static_cast< const PolymorphicDerivedT& >(other)._inv);
    }

    void narrow_threshold_with(const PolymorphicBase& other,
                               const Number& threshold) override {
      this->assert_compatible(other);
      this->_inv
          .narrow_threshold_with(static_cast< const PolymorphicDerivedT& >(
                                     other)
                                     ._inv,
                                 threshold);
    }

    std::unique_ptr< PolymorphicBase > join(
        const PolymorphicBase& other) const override {
      this->assert_compatible(other);
      return std::make_unique< PolymorphicDerivedT >(this->_inv.join(
          static_cast< const PolymorphicDerivedT& >(other)._inv));
    }

    std::unique_ptr< PolymorphicBase > join_loop(
        const PolymorphicBase& other) const override {
      this->assert_compatible(other);
      return std::make_unique< PolymorphicDerivedT >(this->_inv.join_loop(
          static_cast< const PolymorphicDerivedT& >(other)._inv));
    }

    std::unique_ptr< PolymorphicBase > join_iter(
        const PolymorphicBase& other) const override {
      this->assert_compatible(other);
      return std::make_unique< PolymorphicDerivedT >(this->_inv.join_iter(
          static_cast< const PolymorphicDerivedT& >(other)._inv));
    }

    std::unique_ptr< PolymorphicBase > widening(
        const PolymorphicBase& other) const override {
      this->assert_compatible(other);
      return std::make_unique< PolymorphicDerivedT >(this->_inv.widening(
          static_cast< const PolymorphicDerivedT& >(other)._inv));
    }

    std::unique_ptr< PolymorphicBase > widening_threshold(
        const PolymorphicBase& other, const Number& threshold) const override {
      this->assert_compatible(other);
      return std::make_unique< PolymorphicDerivedT >(
          this->_inv
              .widening_threshold(static_cast< const PolymorphicDerivedT& >(
                                      other)
                                      ._inv,
                                  threshold));
    }

    std::unique_ptr< PolymorphicBase > meet(
        const PolymorphicBase& other) const override {
      this->assert_compatible(other);
      return std::make_unique< PolymorphicDerivedT >(this->_inv.meet(
          static_cast< const PolymorphicDerivedT& >(other)._inv));
    }

    std::unique_ptr< PolymorphicBase > narrowing(
        const PolymorphicBase& other) const override {
      this->assert_compatible(other);
      return std::make_unique< PolymorphicDerivedT >(this->_inv.narrowing(
          static_cast< const PolymorphicDerivedT& >(other)._inv));
    }

    std::unique_ptr< PolymorphicBase > narrowing_threshold(
        const PolymorphicBase& other, const Number& threshold) const override {
      this->assert_compatible(other);
      return std::make_unique< PolymorphicDerivedT >(
          this->_inv
              .narrowing_threshold(static_cast< const PolymorphicDerivedT& >(
                                       other)
                                       ._inv,
                                   threshold));
    }

    /// @}
    /// \name Floating point abstract domain methods
    /// @{

    /// By zoush99
    void assign(VariableRef x, int n) override { this->_inv.assign(x, n); }

    void assign(VariableRef x, const Number& n) override {
      this->_inv.assign(x, n);
    }

    void assign(VariableRef x, VariableRef y) override {
      this->_inv.assign(x, y);
    }

    void assign(VariableRef x, const LinearExpressionT& e) override {
      this->_inv.assign(x, e);
    }

    /*    void apply(UnaryOperator op, VariableRef x, VariableRef y) override {
          this->_inv.apply(op, x, y);
        }*/

    void apply(BinaryOperator op,
               VariableRef x,
               VariableRef y,
               VariableRef z) override {
      this->_inv.apply(op, x, y, z);
    }

    void apply(BinaryOperator op,
               VariableRef x,
               VariableRef y,
               const Number& z) override {
      this->_inv.apply(op, x, y, z);
    }

    void apply(BinaryOperator op,
               VariableRef x,
               const Number& y,
               VariableRef z) override {
      this->_inv.apply(op, x, y, z);
    }

    /// By zoush99
    /// { @
    /// \brief Add a linear constraint
    void add(const LinearConstraintT& cst) override { this->_inv.add(cst); }

    /// \brief Add a linear constraint system
    void add(const LinearConstraintSystemT& csts) override {
      this->_inv.add(csts);
    }
    /// @ }

    void add(Predicate pred, VariableRef x, VariableRef y) override {
      this->_inv.add(pred, x, y);
    }

    void add(Predicate pred, VariableRef x, const Number& y) override {
      this->_inv.add(pred, x, y);
    }

    void add(Predicate pred, const Number& x, VariableRef y) override {
      this->_inv.add(pred, x, y);
    }

    void set(VariableRef x, const Interval< Number >& value) override {
      this->_inv.set(x, value);
    }

    void set(VariableRef x, const Congruence< Number >& value) override {
      this->_inv.set(x, value);
    }

    void set(VariableRef x,
             const IntervalCongruence< Number >& value) override {
      this->_inv.set(x, value);
    }

    void refine(VariableRef x, const Interval< Number >& value) override {
      this->_inv.refine(x, value);
    }

    void refine(VariableRef x, const Congruence< Number >& value) override {
      this->_inv.refine(x, value);
    }

    void refine(VariableRef x,
                const IntervalCongruence< Number >& value) override {
      this->_inv.refine(x, value);
    }

    void forget(VariableRef x) override { this->_inv.forget(x); }

    Interval< Number > to_interval(VariableRef x) const override {
      return this->_inv.to_interval(x);
    }

    Interval< Number > to_interval(const LinearExpressionT& e) const override {
      return this->_inv.to_interval(e);
    }

    Congruence< Number > to_congruence(VariableRef x) const override {
      return this->_inv.to_congruence(x);
    }

    Congruence< Number > to_congruence(
        const LinearExpressionT& e) const override {
      return this->_inv.to_congruence(e);
    }

    IntervalCongruence< Number > to_interval_congruence(
        VariableRef x) const override {
      return this->_inv.to_interval_congruence(x);
    }

    IntervalCongruence< Number > to_interval_congruence(
        const LinearExpressionT& e) const override {
      return this->_inv.to_interval_congruence(e);
    }

    /// \todo(annotate)
    LinearConstraintSystemT to_linear_constraint_system() const override {
      return this->_inv.to_linear_constraint_system();
    }

    /// @}
    /// \name Non-negative loop counter abstract domain methods
    /// @{

    void counter_mark(VariableRef x) override { this->_inv.counter_mark(x); }

    void counter_unmark(VariableRef x) override {
      this->_inv.counter_unmark(x);
    }

    void counter_init(VariableRef x, const Number& c) override {
      this->_inv.counter_init(x, c);
    }

    void counter_incr(VariableRef x, const Number& k) override {
      this->_inv.counter_incr(x, k);
    }

    void counter_forget(VariableRef x) override {
      this->_inv.counter_forget(x);
    }

    /// @}

    void dump(std::ostream& o) const override { this->_inv.dump(o); }

  }; // end class PolymorphicDerived

private:
  /// \brief Pointer on the polymorphic base class
  std::unique_ptr< PolymorphicBase > _ptr;

private:
  /// \brief Constructor
  explicit PolymorphicDomain(std::unique_ptr< PolymorphicBase > ptr)
      : _ptr(std::move(ptr)) {}

public:
  /// \brief Create a polymorphic domain with the given abstract value
  template < typename RuntimeDomain >
  explicit PolymorphicDomain(RuntimeDomain inv)
      : _ptr(std::make_unique<
             PolymorphicDerived< remove_cvref_t< RuntimeDomain > > >(
            std::move(inv))) {}

  /// \brief Copy constructor
  PolymorphicDomain(const PolymorphicDomain& other)
      : _ptr(other._ptr->clone()) {}

  /// \brief Move constructor
  PolymorphicDomain(PolymorphicDomain&&) noexcept = default;

  /// \brief Copy assignment operator
  PolymorphicDomain& operator=(const PolymorphicDomain& other) {
    this->_ptr = other._ptr->clone();
    return *this;
  }

  /// \brief Move assignment operator
  PolymorphicDomain& operator=(PolymorphicDomain&&) noexcept = default;

  /// \brief Destructor
  ~PolymorphicDomain() override = default;

  /// \name Core abstract domain methods
  /// @{

  void normalize() override { this->_ptr->normalize(); }

  bool is_bottom() const override { return this->_ptr->is_bottom(); }

  bool is_top() const override { return this->_ptr->is_top(); }

  void set_to_bottom() override { this->_ptr->set_to_bottom(); }

  void set_to_top() override { this->_ptr->set_to_top(); }

  bool leq(const PolymorphicDomain& other) const override {
    return this->_ptr->leq(*other._ptr);
  }

  bool equals(const PolymorphicDomain& other) const override {
    return this->_ptr->equals(*other._ptr);
  }

  void join_with(PolymorphicDomain&& other) override {
    this->_ptr->join_with(std::move(*other._ptr));
  }

  void join_with(const PolymorphicDomain& other) override {
    this->_ptr->join_with(*other._ptr);
  }

  void join_loop_with(PolymorphicDomain&& other) override {
    this->_ptr->join_loop_with(std::move(*other._ptr));
  }

  void join_loop_with(const PolymorphicDomain& other) override {
    this->_ptr->join_loop_with(*other._ptr);
  }

  void join_iter_with(PolymorphicDomain&& other) override {
    this->_ptr->join_iter_with(std::move(*other._ptr));
  }

  void join_iter_with(const PolymorphicDomain& other) override {
    this->_ptr->join_iter_with(*other._ptr);
  }

  void widen_with(const PolymorphicDomain& other) override {
    this->_ptr->widen_with(*other._ptr);
  }

  void widen_threshold_with(const PolymorphicDomain& other,
                            const Number& threshold) override {
    this->_ptr->widen_threshold_with(*other._ptr, threshold);
  }

  void meet_with(const PolymorphicDomain& other) override {
    this->_ptr->meet_with(*other._ptr);
  }

  void narrow_with(const PolymorphicDomain& other) override {
    this->_ptr->narrow_with(*other._ptr);
  }

  void narrow_threshold_with(const PolymorphicDomain& other,
                             const Number& threshold) override {
    this->_ptr->narrow_threshold_with(*other._ptr, threshold);
  }

  PolymorphicDomain join(const PolymorphicDomain& other) const override {
    return PolymorphicDomain(this->_ptr->join(*other._ptr));
  }

  PolymorphicDomain join_loop(const PolymorphicDomain& other) const override {
    return PolymorphicDomain(this->_ptr->join_loop(*other._ptr));
  }

  PolymorphicDomain join_iter(const PolymorphicDomain& other) const override {
    return PolymorphicDomain(this->_ptr->join_iter(*other._ptr));
  }

  PolymorphicDomain widening(const PolymorphicDomain& other) const override {
    return PolymorphicDomain(this->_ptr->widening(*other._ptr));
  }

  PolymorphicDomain widening_threshold(const PolymorphicDomain& other,
                                       const Number& threshold) const override {
    return PolymorphicDomain(
        this->_ptr->widening_threshold(*other._ptr, threshold));
  }

  PolymorphicDomain meet(const PolymorphicDomain& other) const override {
    return PolymorphicDomain(this->_ptr->meet(*other._ptr));
  }

  PolymorphicDomain narrowing(const PolymorphicDomain& other) const override {
    return PolymorphicDomain(this->_ptr->narrowing(*other._ptr));
  }

  PolymorphicDomain narrowing_threshold(
      const PolymorphicDomain& other, const Number& threshold) const override {
    return PolymorphicDomain(
        this->_ptr->narrowing_threshold(*other._ptr, threshold));
  }
  /// @}
  /// \name Floating point abstract domain methods
  /// @{

  /// By zoush99
  void assign(VariableRef x, int n) override { this->_ptr->assign(x, n); }

  void assign(VariableRef x, const Number& n) override {
    this->_ptr->assign(x, n);
  }

  void assign(VariableRef x, VariableRef y) override {
    this->_ptr->assign(x, y);
  }

  void assign(VariableRef x, const LinearExpressionT& e) override {
    this->_ptr->assign(x, e);
  }

  /*
    void apply(UnaryOperator op, VariableRef x, VariableRef y) override {
      this->_ptr->apply(op, x, y);
    }
  */

  void apply(BinaryOperator op,
             VariableRef x,
             VariableRef y,
             VariableRef z) override {
    this->_ptr->apply(op, x, y, z);
  }

  void apply(BinaryOperator op,
             VariableRef x,
             VariableRef y,
             const Number& z) override {
    this->_ptr->apply(op, x, y, z);
  }

  void apply(BinaryOperator op,
             VariableRef x,
             const Number& y,
             VariableRef z) override {
    this->_ptr->apply(op, x, y, z);
  }

  /// By zoush99
  /// { @
  /// \brief Add a linear constraint
  void add(const LinearConstraintT& cst) override { this->_ptr->add(cst); }

  /// \brief Add a linear constraint system
  void add(const LinearConstraintSystemT& csts) override {
    this->_ptr->add(csts);
  }

  /// @ }

  void add(Predicate pred, VariableRef x, VariableRef y) override {
    this->_ptr->add(pred, x, y);
  }

  void add(Predicate pred, VariableRef x, const Number& y) override {
    this->_ptr->add(pred, x, y);
  }

  void add(Predicate pred, const Number& x, VariableRef y) override {
    this->_ptr->add(pred, x, y);
  }

  void set(VariableRef x, const Interval< Number >& value) override {
    this->_ptr->set(x, value);
  }

  void set(VariableRef x, const Congruence< Number >& value) override {
    this->_ptr->set(x, value);
  }

  void set(VariableRef x, const IntervalCongruence< Number >& value) override {
    this->_ptr->set(x, value);
  }

  void refine(VariableRef x, const Interval< Number >& value) override {
    this->_ptr->refine(x, value);
  }

  void refine(VariableRef x, const Congruence< Number >& value) override {
    this->_ptr->refine(x, value);
  }

  void refine(VariableRef x,
              const IntervalCongruence< Number >& value) override {
    this->_ptr->refine(x, value);
  }

  void forget(VariableRef x) override { this->_ptr->forget(x); }

  Interval< Number > to_interval(VariableRef x) const override {
    return this->_ptr->to_interval(x);
  }

  Interval< Number > to_interval(const LinearExpressionT& e) const override {
    return this->_ptr->to_interval(e);
  }

  Congruence< Number > to_congruence(VariableRef x) const override {
    return this->_ptr->to_congruence(x);
  }

  Congruence< Number > to_congruence(
      const LinearExpressionT& e) const override {
    return this->_ptr->to_congruence(e);
  }

  IntervalCongruence< Number > to_interval_congruence(
      VariableRef x) const override {
    return this->_ptr->to_interval_congruence(x);
  }

  IntervalCongruence< Number > to_interval_congruence(
      const LinearExpressionT& e) const override {
    return this->_ptr->to_interval_congruence(e);
  }

  /// \brief How to construct a polymorphic abstract domain? By zoush99
  LinearConstraintSystemT to_linear_constraint_system() const override {
    return this->_ptr->to_linear_constraint_system();
  }

  /// @}
  /// \name Non-negative loop counter abstract domain methods
  /// @{

  void counter_mark(VariableRef x) override { this->_ptr->counter_mark(x); }

  void counter_unmark(VariableRef x) override { this->_ptr->counter_unmark(x); }

  void counter_init(VariableRef x, const Number& c) override {
    this->_ptr->counter_init(x, c);
  }

  void counter_incr(VariableRef x, const Number& k) override {
    this->_ptr->counter_incr(x, k);
  }

  void counter_forget(VariableRef x) override { this->_ptr->counter_forget(x); }

  /// @}

  void dump(std::ostream& o) const override { this->_ptr->dump(o); }

  static std::string name() { return "polymorphic domain"; }

}; // end class PolymorphicDomain

} // end namespace numeric
} // end namespace core
} // end namespace ikos
