CMAKE_MINIMUM_REQUIRED(VERSION 3.15.0)

PROJECT(IBAMR_TUTORIAL LANGUAGES C CXX)
MESSAGE(STATUS "This is CMAKE ${CMAKE_VERSION}")
MESSAGE(STATUS "")
MESSAGE(STATUS "This is IBAMR Tutorial examples")

MESSAGE(STATUS "")
MESSAGE(STATUS "Setting up IBAMR")
FIND_PACKAGE(IBAMR REQUIRED)

MACRO(IBAMR_ADD_EXAMPLE)
  SET(OPTIONS)

  SET(ONE_VALUE_ARGS TARGET_NAME OUTPUT_DIRECTORY OUTPUT_NAME EXAMPLE_GROUP)
  SET(MULTI_VALUE_ARGS SOURCES REQUIRES LINK_TARGETS INPUT_FILES EXTRA_FILES)

  CMAKE_PARSE_ARGUMENTS(EX "${OPTIONS}" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}"
    ${ARGN})

  SET(_failed_requirement)
  SET(_requirements_met TRUE)
  FOREACH(_requirement ${EX_REQUIRES})
    IF(NOT ${${_requirement}})
      SET(_requirements_met FALSE)
      SET(_failed_requirement ${_requirement})
    ENDIF()
  ENDFOREACH()

  IF(${_requirements_met})
    ADD_EXECUTABLE("${EX_TARGET_NAME}" EXCLUDE_FROM_ALL ${EX_SOURCES})
    SET_TARGET_PROPERTIES("${EX_TARGET_NAME}"
      PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY
      "${EX_OUTPUT_DIRECTORY}"
      OUTPUT_NAME
      "${EX_OUTPUT_NAME}")

    # If we have no target link libraries or rely on just boost (which is
    # header-only and, until CMake 3.20 or later, we cannot set a C++ standard
    # on) we need to set up the C++ standard ourselves
    IF("${EX_LINK_TARGETS}" STREQUAL "" OR
       "${EX_LINK_TARGETS}" STREQUAL "BOOST_INTERFACE")
      TARGET_COMPILE_FEATURES("${EX_TARGET_NAME}" PUBLIC cxx_std_11)
    ENDIF()
    IF(NOT "${EX_LINK_TARGETS}" STREQUAL "")
      TARGET_LINK_LIBRARIES("${EX_TARGET_NAME}" PRIVATE ${EX_LINK_TARGETS})
    ENDIF()
    ADD_DEPENDENCIES("${EX_EXAMPLE_GROUP}" "${EX_TARGET_NAME}")

    FOREACH(_input_file ${EX_INPUT_FILES})
      CONFIGURE_FILE("${_input_file}" "${EX_OUTPUT_DIRECTORY}" COPYONLY)
    ENDFOREACH()

    FOREACH(_extra_file ${EX_EXTRA_FILES})
      CONFIGURE_FILE("${_extra_file}" "${EX_OUTPUT_DIRECTORY}" COPYONLY)
    ENDFOREACH()
  ELSE()
    MESSAGE(STATUS "Example ${EX_TARGET_NAME} requires libMesh - skipping")
  ENDIF()
ENDMACRO()

SET(_dirs complex_fluids-ex1 complex_fluids-ex2 IB-ex1 IB-ex4 IBFE-ex4 navier_stokes-ex1 navier_stokes-ex5)
ADD_CUSTOM_TARGET(examples)
FOREACH (_dir ${_dirs})
	ADD_SUBDIRECTORY(${_dir})
ENDFOREACH()
