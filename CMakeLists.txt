cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  td
  VERSION 2.0.0
  DESCRIPTION "A blazing-fast CLI tool to efficiently manage your TODO.md \
directly from the terminal"
  LANGUAGES C
)

configure_file(
  "${CMAKE_SOURCE_DIR}/config/project.h.in"
  "${CMAKE_SOURCE_DIR}/src/project.h"
)

add_executable(
  td
  src/utils/fmt.c
  src/services/storage.c
  src/main.c
)

target_compile_options(td PRIVATE -Wall -Wextra)