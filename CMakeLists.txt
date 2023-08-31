cmake_minimum_required(VERSION 3.0.0)
project(turing_simulator VERSION 0.1.0 LANGUAGES C)
set(C_COMPILE_FLAGS "-Wall -Wextra -Wpedantic -Werror -std=c11")

include(CTest)
enable_testing()

add_executable(turing_simulator src/main.c)
target_include_directories(turing_simulator PRIVATE src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
