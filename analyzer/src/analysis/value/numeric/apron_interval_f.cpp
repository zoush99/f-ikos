//
// Created by zou on 3/14/24.
//
#ifdef HAS_APRON
#include <ikos/core/domain/numeric/apron.hpp>
#endif

#include <ikos/analyzer/analysis/value/numeric_domain.hpp>

#include <ikos/analyzer/exception.hpp>

namespace ikos {
namespace analyzer {
namespace value {

#ifdef HAS_APRON
namespace {

using RuntimeNumericDomain = core::numeric::
    ApronDomain< core::numeric::apron::Interval, FNumber, Variable* >;
} // end anonymous namespace
#endif

NumericAbstractDomain make_top_numeric_apron_interval() {
#ifdef HAS_APRON
  return NumericAbstractDomain(RuntimeNumericDomain::top());
#else
  throw LogicError("ikos was compiled without apron support");
#endif
}

NumericAbstractDomain make_bottom_numeric_apron_interval() {
#ifdef HAS_APRON
  return NumericAbstractDomain(RuntimeNumericDomain::bottom());
#else
  throw LogicError("ikos was compiled without apron support");
#endif
}

} // end namespace value
} // end namespace analyzer
} // end namespace ikos
