#*******************************************************************************
#
# Author: Maxime Arthaud
#
# Contact: ikos@lists.nasa.gov
#
# Notices:
#
# Copyright (c) 2011-2019 United States Government as represented by the
# Administrator of the National Aeronautics and Space Administration.
# All Rights Reserved.
#
# Disclaimers:
#
# No Warranty: THE SUBJECT SOFTWARE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY OF
# ANY KIND, EITHER EXPRESSED, IMPLIED, OR STATUTORY, INCLUDING, BUT NOT LIMITED
# TO, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL CONFORM TO SPECIFICATIONS,
# ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
# OR FREEDOM FROM INFRINGEMENT, ANY WARRANTY THAT THE SUBJECT SOFTWARE WILL BE
# ERROR FREE, OR ANY WARRANTY THAT DOCUMENTATION, IF PROVIDED, WILL CONFORM TO
# THE SUBJECT SOFTWARE. THIS AGREEMENT DOES NOT, IN ANY MANNER, CONSTITUTE AN
# ENDORSEMENT BY GOVERNMENT AGENCY OR ANY PRIOR RECIPIENT OF ANY RESULTS,
# RESULTING DESIGNS, HARDWARE, SOFTWARE PRODUCTS OR ANY OTHER APPLICATIONS
# RESULTING FROM USE OF THE SUBJECT SOFTWARE.  FURTHER, GOVERNMENT AGENCY
# DISCLAIMS ALL WARRANTIES AND LIABILITIES REGARDING THIRD-PARTY SOFTWARE,
# IF PRESENT IN THE ORIGINAL SOFTWARE, AND DISTRIBUTES IT "AS IS."
#
# Waiver and Indemnity:  RECIPIENT AGREES TO WAIVE ANY AND ALL CLAIMS AGAINST
# THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS, AS WELL
# AS ANY PRIOR RECIPIENT.  IF RECIPIENT'S USE OF THE SUBJECT SOFTWARE RESULTS
# IN ANY LIABILITIES, DEMANDS, DAMAGES, EXPENSES OR LOSSES ARISING FROM SUCH
# USE, INCLUDING ANY DAMAGES FROM PRODUCTS BASED ON, OR RESULTING FROM,
# RECIPIENT'S USE OF THE SUBJECT SOFTWARE, RECIPIENT SHALL INDEMNIFY AND HOLD
# HARMLESS THE UNITED STATES GOVERNMENT, ITS CONTRACTORS AND SUBCONTRACTORS,
# AS WELL AS ANY PRIOR RECIPIENT, TO THE EXTENT PERMITTED BY LAW.
# RECIPIENT'S SOLE REMEDY FOR ANY SUCH MATTER SHALL BE THE IMMEDIATE,
# UNILATERAL TERMINATION OF THIS AGREEMENT.
#
#*****************************************************************************/

cmake_minimum_required(VERSION 3.4.3 FATAL_ERROR)

if (POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

project(ikos-core)

#
# Build settings
#

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR
    "In-source builds are not allowed. Please clean your source tree and try again.")
endif()

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build" FORCE)
endif()

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "Install directory" FORCE)
endif()

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
  message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
  message(STATUS "CMake version: ${CMAKE_VERSION}")
  message(STATUS "CMake generator: ${CMAKE_GENERATOR}")
endif()

#
# Dependency checks
#

# Add path for custom modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")

set(CUSTOM_BOOST_ROOT "" CACHE PATH "Path to custom boost installation")
if (CUSTOM_BOOST_ROOT)
  set(BOOST_ROOT "${CUSTOM_BOOST_ROOT}")
  set(Boost_NO_SYSTEM_PATHS TRUE)
endif()

find_package(Boost 1.55.0 REQUIRED
             COMPONENTS unit_test_framework)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

find_package(GMP REQUIRED)
include_directories(SYSTEM ${GMP_INCLUDE_DIR})
include_directories(SYSTEM ${GMPXX_INCLUDE_DIR})

find_package(TBB 2 REQUIRED)
include_directories(SYSTEM ${TBB_INCLUDE_DIRS})

find_package(APRON)
if (APRON_FOUND)
  include_directories(SYSTEM ${APRON_INCLUDE_DIRS})
endif()

#find_package(LLVM REQUIRED) # By zoush99
#include_directories(SYSTEM ${LLVM_INCLUDE_DIR}) # By zoush99

#
# Compiler flags
#

include(AddFlagUtils)
add_compiler_flag(REQUIRED "CXX14" "-std=c++1y")
add_compiler_flag(REQUIRED "FVISIBILITY_INLINES_HIDDEN" "-fvisibility-inlines-hidden")

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compiler_flag(REQUIRED "WEVERYTHING" "-Weverything")
  add_compiler_flag(OPTIONAL "WNO_SWITCH_ENUM" "-Wno-switch-enum")
  add_compiler_flag(OPTIONAL "WNO_PADDED" "-Wno-padded")
  add_compiler_flag(OPTIONAL "WNO_CXX98_COMPAT" "-Wno-c++98-compat")
  add_compiler_flag(OPTIONAL "WNO_CXX98_COMPAT_PEDANTIC" "-Wno-c++98-compat-pedantic")
  add_compiler_flag(OPTIONAL "WNO_COVERED_SWITCH_DEFAULT" "-Wno-covered-switch-default")
  add_compiler_flag(OPTIONAL "WNO_WEAK_VTABLES" "-Wno-weak-vtables")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compiler_flag(REQUIRED "WALL" "-Wall")
  add_compiler_flag(REQUIRED "WEXTRA" "-Wextra")
  add_compiler_flag(OPTIONAL "WNO_MAYBE_UNINITIALIZED" "-Wno-maybe-uninitialized")
  add_compiler_flag(OPTIONAL "WNO_REDUNDANT_MOVE" "-Wno-redundant-move")
endif()

#
# Targets
#

include_directories(include)

# install headers
install(DIRECTORY include/
  DESTINATION include
  FILES_MATCHING
  PATTERN "*.hpp"
)

#
# Unit tests
#

enable_testing()
add_custom_target(build-core-tests)
add_subdirectory(test/unit EXCLUDE_FROM_ALL)

#
# Doxygen
#

find_package(Doxygen)
if (DOXYGEN_FOUND)
  configure_file(doc/doxygen/Doxyfile.in doc/Doxyfile @ONLY)
  add_custom_target(doxygen-core
    ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/doc/Doxyfile"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    COMMENT "Generating IKOS CORE API documentation with Doxygen" VERBATIM
  )
  install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc/html" DESTINATION doc/ikos OPTIONAL)
endif()

#
# If it's the top level CMakeLists.txt, Add some aliases
#

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND}
    DEPENDS build-core-tests)
  add_custom_target(doc DEPENDS doxygen-core)
endif()
