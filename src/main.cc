#include "project.hpp"
#include <CLI/CLI.hpp>

int main(int argc, char *argv[]) {
  CLI::App app{PROJECT_DESCRIPTION};

  // Start parsing the arguments
  CLI11_PARSE(app, argc, argv);
}