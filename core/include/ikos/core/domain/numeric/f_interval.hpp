//
// Created by zou on 1/11/24.
//

/*******************************************************************************
 *
 * \file
 * \brief Standard domain of f-intervals
 *
 * Author: Arnaud J. Venet
 *
 * Contributors:
 *   * Alexandre C. D. Wimmers
 *   * Maxime Arthaud
 *
 * Contact: ikos@lists.nasa.gov
 *
 * Notices:
 *
 * Copyright (c) 2011-2019 United States Government as represented by the
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

#include <ikos/core/domain/numeric/abstract_domain.hpp>
#include <ikos/core/domain/numeric/linear_interval_solver.hpp>
#include <ikos/core/domain/numeric/separate_domain.hpp>
#include <ikos/core/number/bound.hpp>
#include <ikos/core/value/numeric/congruence.hpp>
#include <ikos/core/value/numeric/interval.hpp>
#include <ikos/core/value/numeric/interval_congruence.hpp>

namespace ikos {
namespace core {
namespace numeric {

/// \brief Trim the bounds of the given interval
template < typename Number >
inline Interval< Number > trim_bound(const Interval< Number >& i,
                                     const Number&) {
//  assert_compatible(i, b);
  ikos_assert(!i.is_bottom());
  return i;
}

/// \brief Interval abstract domain
template < typename Number,
           typename VariableRef,
           std::size_t MaxReductionCycles = 10 >
class FIntervalDomain final
    : public numeric::AbstractDomain<
          Number,
          VariableRef,
          FIntervalDomain< Number, VariableRef, MaxReductionCycles > > {
public:
  using IntervalT = Interval< Number >;
  using CongruenceT = Congruence< Number >;
  using IntervalCongruenceT = IntervalCongruence< Number >;
  using LinearExpressionT = LinearExpression< Number, VariableRef >;
  using LinearConstraintT = LinearConstraint< Number, VariableRef >;
  using LinearConstraintSystemT = LinearConstraintSystem< Number, VariableRef >;

private:
  using SeparateDomainT = SeparateDomain< Number, VariableRef, IntervalT >;
  using LinearIntervalSolverT =
      LinearIntervalSolver< Number, VariableRef, FIntervalDomain >;
  using Parent = numeric::AbstractDomain< Number, VariableRef, FIntervalDomain >;

public:
  using Iterator = typename SeparateDomainT::Iterator;

private:
  SeparateDomainT _inv;

private:
  /// \brief Private constructor
  explicit FIntervalDomain(SeparateDomainT inv) : _inv(std::move(inv)) {}

public:
  /// \brief Create the top abstract value
  static FIntervalDomain top() { return FIntervalDomain(SeparateDomainT::top()); }

  /// \brief Create the bottom abstract value
  static FIntervalDomain bottom() {
    return FIntervalDomain(SeparateDomainT::bottom());
  }

  /// \brief Copy constructor
  FIntervalDomain(const FIntervalDomain&) noexcept = default;

  /// \brief Move constructor
  FIntervalDomain(FIntervalDomain&&) noexcept = default;

  /// \brief Copy assignment operator
  FIntervalDomain& operator=(const FIntervalDomain&) noexcept = default;

  /// \brief Move assignment operator
  FIntervalDomain& operator=(FIntervalDomain&&) noexcept = default;

  /// \brief Destructor
  ~FIntervalDomain() override = default;

  /// \brief Begin iterator over the pairs (variable, interval)
  Iterator begin() const { return this->_inv.begin(); }

  /// \brief End iterator over the pairs (variable, interval)
  Iterator end() const { return this->_inv.end(); }

  void normalize() override {}

  bool is_bottom() const override { return this->_inv.is_bottom(); }

  bool is_top() const override { return this->_inv.is_top(); }

  void set_to_bottom() override { this->_inv.set_to_bottom(); }

  void set_to_top() override { this->_inv.set_to_top(); }

  bool leq(const FIntervalDomain& other) const override {
    return this->_inv.leq(other._inv);
  }

  bool equals(const FIntervalDomain& other) const override {
    return this->_inv.equals(other._inv);
  }

  void join_with(const FIntervalDomain& other) override {
    this->_inv.join_with(other._inv);
  }

  void join_loop_with(const FIntervalDomain& other) override {
    this->_inv.join_loop_with(other._inv);
  }

  void join_iter_with(const FIntervalDomain& other) override {
    this->_inv.join_iter_with(other._inv);
  }

  void widen_with(const FIntervalDomain& other) override {
    this->_inv.widen_with(other._inv);
  }

  void widen_threshold_with(const FIntervalDomain& other,
                            const Number& threshold) override {
    this->_inv.widen_threshold_with(other._inv, threshold);
  }

  void meet_with(const FIntervalDomain& other) override {
    this->_inv.meet_with(other._inv);
  }

  void narrow_with(const FIntervalDomain& other) override {
    this->_inv.narrow_with(other._inv);
  }

  void narrow_threshold_with(const FIntervalDomain& other,
                             const Number& threshold) override {
    this->_inv.narrow_threshold_with(other._inv, threshold);
  }

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

  void add(const LinearConstraintT& cst) override {
    if (this->is_bottom()) {
      return;
    }

    LinearIntervalSolverT solver(MaxReductionCycles);
    solver.add(cst);
    solver.run(*this);
  }

  void add(const LinearConstraintSystemT& csts) override {
    if (this->is_bottom()) {
      return;
    }

    LinearIntervalSolverT solver(MaxReductionCycles);
    solver.add(csts);
    solver.run(*this);
  }

  /// \todo(Further modifications are needed here, as this was copied without
  /// changes from machine integer types. Some of the involved functions do not
  /// exist, and correctness has not been considered.) By zoush99
  /// { @
  /// \brief Add the constraint `x pred y`
  void add(Predicate pred, VariableRef x, VariableRef y) override {
    return;
  }
  void add(Predicate pred, VariableRef x, const Number& y) override {
    return;
  }
  void add(Predicate pred, const Number& x, VariableRef y) override {
    return;
  }
  /*void add(Predicate pred, VariableRef x, VariableRef y) override {
    if (this->is_bottom()) {
      return;
    }

    Interval< Number > xi = this->_inv.get(x);
    Interval< Number > yi = this->_inv.get(y);

    switch (pred) {
      case Predicate::EQ: {
        Interval< Number > i = xi.meet(yi);
        this->_inv.set(x, i);
        this->_inv.set(y, i);
      } break;
      case Predicate::NE: {
        if (x == y) {
          this->set_to_bottom();
          return;
        }
        if (xi.singleton()) {
          this->_inv.set(y, *//*yi = *//* trim_bound(yi, *xi.singleton()));
        }
        if (yi.singleton()) {
          this->_inv.set(x, *//*xi = *//* trim_bound(xi, *yi.singleton()));
        }
      } break;
      case Predicate::GT: {
        this->add(Predicate::LT, y, x);
      } break;
      case Predicate::GE: {
        this->add(Predicate::LE, y, x);
      } break;
        /// \brief Key factors. By zoush99
        /// \details It's important to note that the greater than and less than
        /// relations must exclude equality, but currently, equality is not
        /// excluded here. It will need to be modified later.
      case Predicate::LT: {
        if (x == y) {
          this->set_to_bottom();
          return;
        }
        if (yi.ub().is_minus_infinity() || xi.lb().is_plus_infinity()) {
          this->set_to_bottom();
          return;
        }
        this->_inv.refine(x, yi.lower_half_line());
        this->_inv.refine(y, xi.upper_half_line());
      } break;
      case Predicate::LE: {
        this->_inv.refine(x, yi.lower_half_line());
        this->_inv.refine(y, xi.upper_half_line());
      } break;
    }
  }

  /// (Further modifications are needed here, as this was copied without
  /// changes from machine integer types. Some of the involved functions do not
  /// exist, and correctness has not been considered.) By zoush99
  /// \brief Add the constraint `x pred y`
  void add(Predicate pred, VariableRef x, const Number& y) override {
    if (this->is_bottom()) {
      return;
    }

    Interval< Number > xi = this->_inv.get(x);
    Interval< Number > yi(y);

    switch (pred) {
      case Predicate::EQ: {
        Interval< Number > i = xi.meet(yi);
        this->_inv.set(x, i);
      } break;
      case Predicate::NE: {
        this->_inv.set(x, *//*xi = *//*trim_bound(xi, y));
      } break;
      case Predicate::GT: {
        if (y.is_max()) {
          this->set_to_bottom();
          return;
        }
        this->_inv.refine(x, yi.upper_half_line());
      } break;
      case Predicate::GE: {
        this->_inv.refine(x, yi.upper_half_line());
      } break;
      case Predicate::LT: {
        if (y.is_min()) {
          this->set_to_bottom();
          return;
        }
        this->_inv.refine(x, yi.lower_half_line());
      } break;
      case Predicate::LE: {
        this->_inv.refine(x, yi.lower_half_line());
      } break;
    }
  }

  /// \brief Add the constraint `x pred y`
  void add(Predicate pred, const Number& x, VariableRef y) override {
    Parent::add(pred, x, y);
  }
  /// @ }*/

  void set(VariableRef x, const IntervalT& value) override {
    this->_inv.set(x, value);
  }

  void set(VariableRef x, const CongruenceT& value) override {
    if (this->is_bottom()) {
      return;
    } else if (value.is_bottom()) {
      this->set_to_bottom();
    } else {
      boost::optional< Number > n = value.singleton();
      if (n) {
        this->_inv.set(x, IntervalT(*n));
      } else {
        this->_inv.forget(x);
      }
    }
  }

  void set(VariableRef x, const IntervalCongruenceT& value) override {
    this->_inv.set(x, value.interval());
  }

  void refine(VariableRef x, const IntervalT& value) override {
    this->_inv.refine(x, value);
  }

  void refine(VariableRef x, const CongruenceT& value) override {
    if (this->is_bottom()) {
      return;
    } else if (value.is_bottom()) {
      this->set_to_bottom();
    } else {
      IntervalCongruenceT iv(this->_inv.get(x), value);
      this->_inv.set(x, iv.interval());
    }
  }

  void refine(VariableRef x, const IntervalCongruenceT& value) override {
    if (this->is_bottom()) {
      return;
    } else if (value.is_bottom()) {
      this->set_to_bottom();
    } else {
      IntervalCongruenceT iv(this->_inv.get(x));
      iv.meet_with(value);
      this->_inv.set(x, iv.interval());
    }
  }

  void forget(VariableRef x) override { this->_inv.forget(x); }

  IntervalT to_interval(VariableRef x) const override {
    return this->_inv.get(x);
  }

  IntervalT to_interval(const LinearExpressionT& e) const override {
    return this->_inv.project(e);
  }

  CongruenceT to_congruence(VariableRef x) const override {
    if (this->is_bottom()) {
      return CongruenceT::bottom();
    }

    boost::optional< Number > n = this->_inv.get(x).singleton();
    if (n) {
      return CongruenceT(*n);
    } else {
      return CongruenceT::top();
    }
  }

  CongruenceT to_congruence(const LinearExpressionT& e) const override {
    return Parent::to_congruence(e);
  }

  IntervalCongruenceT to_interval_congruence(VariableRef x) const override {
    return IntervalCongruenceT(this->_inv.get(x));
  }

  IntervalCongruenceT to_interval_congruence(
      const LinearExpressionT& e) const override {
    return Parent::to_interval_congruence(e);
  }

  LinearConstraintSystemT to_linear_constraint_system() const override {
    if (this->is_bottom()) {
      return LinearConstraintSystemT(LinearConstraintT::contradiction());
    }

    LinearConstraintSystemT csts;
    for (auto it = this->begin(), et = this->end(); it != et; ++it) {
      csts.add(within_interval(it->first, it->second));
    }

    return csts;
  }

  void dump(std::ostream& o) const override { this->_inv.dump(o); }

  static std::string name() { return "interval domain"; }

}; // end class FIntervalDomain

} // end namespace numeric
} // end namespace core
} // end namespace ikos
