cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  td
  VERSION 2.0.0
  DESCRIPTION "A blazing-fast CLI tool to efficiently manage your todos \
directly from the terminal"
  LANGUAGES C
)

configure_file(
  "${CMAKE_SOURCE_DIR}/config/project.hpp.in"
  "${CMAKE_SOURCE_DIR}/src/project.hpp"
)

add_executable(
  td
  src/utils/fmt.c
  src/main.c
)

target_link_libraries(td PRIVATE ncurses tinfo)
