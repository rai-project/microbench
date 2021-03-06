# This file generated automatically by:
#   generate_sugar_files.py
# see wiki for more info:
#   https://github.com/ruslo/sugar/wiki/Collecting-sources

if(DEFINED SRC_SCOPE_INIT_SUGAR_CMAKE_)
  return()
else()
  set(SRC_SCOPE_INIT_SUGAR_CMAKE_ 1)
endif()

include(sugar_files)

sugar_files(
    BENCHMARK_HEADERS
    cuda.hpp
    flags.hpp
    init.hpp
    logger.hpp
)

sugar_files(
    BENCHMARK_SOURCES
    cuda.cpp
    flags.cpp
    init.cpp
    logger.cpp
)

