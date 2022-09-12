cmake_minimum_required(VERSION 3.13)
project(cmake_testapp)

set(CMAKE_CXX_STANDARD 14)

add_executable(cmake_testapp adventure.c items.h items.c rooms.h rooms.c)