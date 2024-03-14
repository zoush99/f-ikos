//
// Created by zou on 1/11/24.
//
#include <ikos/analyzer/analysis/value/numeric_domain.hpp>
#include <ikos/core/domain/numeric/f_interval.hpp>

namespace ikos {
namespace analyzer {
namespace value {

namespace {

using RuntimeNumericDomain =
    core::numeric::FIntervalDomain< FNumber, Variable* >; // By zoush99

} // end anonymous namespace

NumericAbstractDomain make_top_numeric_interval() { // By zoush99
  return NumericAbstractDomain(RuntimeNumericDomain::top());
}

NumericAbstractDomain make_bottom_numeric_interval() { // By zoush99
  return NumericAbstractDomain(RuntimeNumericDomain::bottom());
}

} // end namespace value
} // end namespace analyzer
} // end namespace ikos
