# Compiler and flags
CC = clang++
CXX_FLAGS = -Wall -Wextra -std=c++23 -O2 -I$(FMT_DIR)/include

# Directories
SRC_DIR = ./src
BUILD_DIR = ./build
DEPS_DIR = ./deps

# Source and output files
SRC_FILE = $(SRC_DIR)/main.cc
TARGET = $(BUILD_DIR)/todocxx

# FMT version
FMT_VERSION = 11.1.2
FMT_ARCHIVE = fmt-$(FMT_VERSION).zip
FMT_URL = https://github.com/fmtlib/fmt/releases/download/$(FMT_VERSION)/$(FMT_ARCHIVE)
FMT_DIR = $(DEPS_DIR)/fmt-$(FMT_VERSION)
FMT_LIB = $(FMT_DIR)/build/libfmt.a

# Phony targets
.PHONY: all clean ensure_dir install deps fmt

# Default target
all: ensure_dir $(TARGET)

# Ensure the build directory exists
ensure_dir:
	@mkdir -p $(BUILD_DIR)

# Build the target
$(TARGET): $(SRC_FILE) $(FMT_LIB)
	@$(CC) $(CXX_FLAGS) $< $(FMT_LIB) -o $@ -static
	@echo "Built target: $@"

# Install the todocxx binary
install: $(TARGET)
	@mkdir -p ~/.local/bin
	@cp $(TARGET) ~/.local/bin/
	@echo "Installed todocxx to ~/.local/bin/"

# Download and build fmt as a static library
deps: fmt

fmt: $(FMT_LIB)

$(FMT_LIB):
	@mkdir -p $(DEPS_DIR)
	@cd $(DEPS_DIR) && \
		curl -LO $(FMT_URL) && \
		unzip -o $(FMT_ARCHIVE) || exit 1
	@mkdir -p $(FMT_DIR)/build
	@cd $(FMT_DIR)/build && \
		cmake -DCMAKE_POSITION_INDEPENDENT_CODE=TRUE -DBUILD_SHARED_LIBS=OFF .. && \
		cmake --build . || exit 1
	@echo "Built static fmt library: $(FMT_LIB)"

# Clean up build artifacts
clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(DEPS_DIR)/fmt-$(FMT_VERSION) $(DEPS_DIR)/$(FMT_ARCHIVE)
	@echo "Cleaned build and dependencies"
