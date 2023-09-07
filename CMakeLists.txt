cmake_minimum_required(VERSION 3.0.0)
project(turing_simulator VERSION 0.1.0 LANGUAGES C)
add_compile_options(-Wall -Wextra -Wpedantic -Werror -std=c11 -pg)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")

include(CTest)
enable_testing()

set(SOURCES
    src/turing.c
)

set(HEADERS
    src/turing.h
)
add_executable(turing_simulator src/main.c ${SOURCES} ${HEADERS})
target_include_directories(turing_simulator PRIVATE src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

project(benchmarks)

