cmake_minimum_required(VERSION 3.17.0)
project(Battle_Ship)

include(CTest)
enable_testing()
set(FilesForExec
    "src/battle.cpp"
    "src/board.cpp"
    "src/piece.cpp"
    "src/vessel.cpp"
    "src/rules.cpp"
    "include/board.h"
    "include/rules.h"
    "include/piece.h"
    "include/vessel.h"
    "include/sloop.h"
    "include/player.h"
    )
add_executable(Battle_Ship ${FilesForExec})
target_include_directories(Battle_Ship PUBLIC include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include(CPack)
