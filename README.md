# 📝 td

**td** is a blazing-fast CLI tool to efficiently manage your `TODO.md` directly from the terminal. It's fast!

## 🚀 Installation

Follow these steps to build and install the program:

**Prerequisites**

Make sure you have the following dependencies:

- **CMake** (version 3.10 or higher)
- **A C compiler** (e.g., GCC or Clang)
- **uthash** and **utlist** libraries (can be installed via your system's package manager)

**Building the Project**

1. Clone the repository:

   ```bash
   git clone https://github.com/2giosangmitom/td.git
   cd td
   ```

2. Create the build directory and configure the project with CMake:

   ```bash
   cmake -B build
   ```

3. Build the project:

   ```bash
   cmake --build build
   ```

4. See `--help` to know how to use this tool:

   ```
   ./build/td --help
   ```

The compiled binary will be located at `build/td` (or `build/td.exe` on Windows).
