/*******************************************************************************
 *
 * \file
 * \brief Implement make_(top|bottom)_machine_int_apron_zonotopes
 *
 * Author: zoush99
 *
 ******************************************************************************/

 #ifdef HAS_APRON
 #include <ikos/core/domain/machine_int/numeric_domain_adapter.hpp>
 #include <ikos/core/domain/numeric/apron.hpp>
 #endif
 
 #include <ikos/analyzer/analysis/value/machine_int_domain.hpp>
 #include <ikos/analyzer/exception.hpp>
 
 namespace ikos {
 namespace analyzer {
 namespace value {
 
 #ifdef HAS_APRON
 namespace {
 
 using RuntimeNumericDomain = core::numeric::
     ApronDomain< core::numeric::apron::Zonotope, ZNumber, Variable* >;
 using RuntimeMachineIntDomain =
     core::machine_int::NumericDomainAdapter< Variable*, RuntimeNumericDomain >;
 
 } // end anonymous namespace
 #endif
 
 MachineIntAbstractDomain make_top_machine_int_apron_zonotope() {
 #ifdef HAS_APRON
   return MachineIntAbstractDomain(
       RuntimeMachineIntDomain(RuntimeNumericDomain::top()));
 #else
   throw LogicError("ikos was compiled without apron support");
 #endif
 }
 
 MachineIntAbstractDomain make_bottom_machine_int_apron_zonotope() {
 #ifdef HAS_APRON
   return MachineIntAbstractDomain(
       RuntimeMachineIntDomain(RuntimeNumericDomain::bottom()));
 #else
   throw LogicError("ikos was compiled without apron support");
 #endif
 }
 
 } // end namespace value
 } // end namespace analyzer
 } // end namespace ikos
 