cmake_minimum_required(VERSION 3.17.0)
project(Battle_Ship)

include(CTest)
enable_testing()

add_executable(Battle_Ship battle.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include(CPack)
