###############################################################################
#
# Find flang binary.
#
# Author: zoush99
###############################################################################

if (NOT FLANG_FOUND)
  find_program(FLANG_EXECUTABLE CACHE NAMES flang DOC "Path to flang binary")

  set(FLANG_EXECUTABLE "/home/zou/Documents/build-flang/classic-flang-llvm-project/build/bin")
  if (FLANG_EXECUTABLE)
    get_filename_component(FLANG_BINARY_DIR "${FLANG_EXECUTABLE}" DIRECTORY)
  endif()

#  if (FLANG_EXECUTABLE)
#    # Detect the version using `flang --version`
#    execute_process(
#      COMMAND ${FLANG_EXECUTABLE} --version
#      RESULT_VARIABLE HAD_ERROR
#      OUTPUT_VARIABLE FLANG_VERSION_OUTPUT
#      OUTPUT_STRIP_TRAILING_WHITESPACE
#    )
#    if (HAD_ERROR)
#      message(FATAL_ERROR "flang failed with status: ${HAD_ERROR}")
#    endif()
#    if (NOT (FLANG_VERSION_OUTPUT MATCHES "flang version ([0-9]+(\\.[0-9]+)*)"))
#      message(FATAL_ERROR "unexpected output for `flang --version`: ${FLANG_VERSION_OUTPUT}")
#    endif()
#    set(FLANG_VERSION "${CMAKE_MATCH_1}")
#  endif()

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(Flang
    REQUIRED_VARS
      FLANG_EXECUTABLE
      FLANG_VERSION
    VERSION_VAR
      FLANG_VERSION
    FAIL_MESSAGE
      "Could NOT find Flang. Please provide -DFLANG_EXECUTABLE=/path/to/flang")
endif()
