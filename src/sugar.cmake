# This file generated automatically by:
#   generate_sugar_files.py
# see wiki for more info:
#   https://github.com/ruslo/sugar/wiki/Collecting-sources

if(DEFINED SRC_SUGAR_CMAKE_)
  return()
else()
  set(SRC_SUGAR_CMAKE_ 1)
endif()

include(sugar_files)
include(sugar_include)

sugar_include(gemm)
sugar_include(stream)
sugar_include(network)
sugar_include(launch)
sugar_include(vectoradd)
sugar_include(layers)
sugar_include(cuda-numa)
sugar_include(init)
sugar_include(memcpy)
sugar_include(conv)
sugar_include(utils)
sugar_include(reduction)
sugar_include(gemv)
sugar_include(lock)
sugar_include(axpy)
sugar_include(framework)
sugar_include(atomic)

sugar_files(
    BENCHMARK_HEADERS
    config.hpp
)

sugar_files(
    BENCHMARK_SOURCES
    main.cpp
)

