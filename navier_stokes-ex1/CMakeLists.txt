## ---------------------------------------------------------------------
##
## Copyright (c) 2020 - 2020 by the IBAMR developers
## All rights reserved.
##
## This file is part of IBAMR.
##
## IBAMR is free software and is distributed under the 3-clause BSD
## license. The full text of the license can be found in the file
## COPYRIGHT at the top level directory of IBAMR.
##
## ---------------------------------------------------------------------

IBAMR_ADD_EXAMPLE(
  TARGET_NAME
    "navier_stokes-ex1-2d"
  OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/navier_stokes-ex1"
  OUTPUT_NAME
    main2d
  EXAMPLE_GROUP
    examples
  SOURCES
    example.cpp
  LINK_TARGETS
    IBAMR::IBAMR2d
  INPUT_FILES
    input2d
  )

IBAMR_ADD_EXAMPLE(
  TARGET_NAME
    "navier_stokes-ex1-3d"
  OUTPUT_DIRECTORY
    "${CMAKE_BINARY_DIR}/navier_stokes-ex1"
  OUTPUT_NAME
    main3d
  EXAMPLE_GROUP
    examples
  SOURCES
    example.cpp
  LINK_TARGETS
    IBAMR::IBAMR3d
  INPUT_FILES
    input3d
  )

ADD_CUSTOM_TARGET(navier_stokes-ex1)
ADD_DEPENDENCIES(navier_stokes-ex1 navier_stokes-ex1-2d navier_stokes-ex1-3d)
