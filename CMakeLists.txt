cmake_minimum_required(VERSION 3.0.0)
project(mpl VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

find_library(gmp GMP REQUIRED)
add_executable(mpl main.cpp lexer.cpp parser.cpp)
target_link_libraries(mpl gmp gmpxx)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)