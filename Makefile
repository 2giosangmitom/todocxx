# Compiler and flags
CC = clang++
CXX_FLAGS = -Wall -Wextra -std=c++17
FMT_FLAGS = -lfmt

# Directories
SRC_DIR = ./src
BUILD_DIR = ./build

# Source and output files
SRC_FILE = $(SRC_DIR)/main.cc
TARGET = $(BUILD_DIR)/todocxx

# Phony targets
.PHONY: all clean ensure_dir

# Default target
all: ensure_dir $(TARGET)

# Ensure build directory exists
ensure_dir:
	@mkdir -p $(BUILD_DIR)

# Build the target
$(TARGET): $(SRC_FILE)
	@$(CC) $(CXX_FLAGS) $(FMT_FLAGS) $< -o $@

# Clean up build artifacts
clean:
	@rm -rf $(BUILD_DIR)
