CC = clang++
CXX_FLAGS = -Wall -Wextra -std=c++17
FMT_FLAGS = -lfmt

SRC_FILES = ./src/main.cc

ensure_dir:
	@if [ ! -d "./build" ]; then \
		mkdir build; \
	fi \

build: ensure_dir
	@$(CC) $(CXX_FLAGS) $(FMT_FLAGS) $(SRC_FILES) -o build/todocxx
