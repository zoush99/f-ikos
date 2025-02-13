//
// Created by zou on 1/13/24.
//
/*******************************************************************************
 *
 * \file
 * \brief Numeric abstract domain used by the value analysis
 *
 * Author: zoush99
 *
 ******************************************************************************/

#include <ikos/analyzer/analysis/value/numeric_domain.hpp>

namespace ikos {
namespace analyzer {
namespace value {

// By zoush99
NumericAbstractDomain make_top_numeric_abstract_value(
    FNumberDomainOption domain) {
  switch (domain) {
    case FNumberDomainOption::ApronInterval :
      return make_top_numeric_apron_interval();
    case FNumberDomainOption::ApronOctagon :
      return make_top_numeric_apron_octagon();
    case FNumberDomainOption::ApronPolkaPolyhedra:
      return make_top_numeric_apron_polka_polyhedra();
    default: {
      ikos_unreachable("unreachable");
    }
  }
}

NumericAbstractDomain make_bottom_numeric_abstract_value(
    FNumberDomainOption domain) {
  switch (domain) {
    case FNumberDomainOption::ApronInterval:
      return make_bottom_numeric_apron_interval();
    case FNumberDomainOption::ApronOctagon:
      return make_bottom_numeric_apron_octagon();
    case FNumberDomainOption::ApronPolkaPolyhedra:
      return make_bottom_numeric_apron_polka_polyhedra();
    default: {
      ikos_unreachable("unreachable");
    }
  }
}

} // end namespace value
} // end namespace analyzer
} // end namespace ikos
