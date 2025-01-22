#include "./cli/table.hpp"
#include "./io/csv.hpp"
#include <cxxopts.hpp>
#include <fmt/color.h>
#include <fmt/core.h>
#include <string>
#include <vector>

// clang-format off
#if defined(_WIN32)
  #define PLATFORM "windows"
#elif defined(__linux__)
  #define PLATFORM "linux"
#elif defined(__APPLE__)
  #define PLATFORM "macos"
#endif
// clang-format on

int main(int argc, char *argv[]) {
  const std::string app_name = "todocxx";
  const std::string app_desc =
      "A blazing-fast CLI tool to efficiently manage your todos directly from "
      "the terminal\n";
  const std::string app_version = "1.0.0";

  cxxopts::Options options(app_name, app_desc);
  options.set_tab_expansion().set_width(100);

  // clang-format off
  options.add_options("Operations")
      ("a,add", "Add a new todo with a title", cxxopts::value<std::string>(), "<TITLE>")
      ("u,update", "Update a todo by ID", cxxopts::value<unsigned int>(), "<TODO_ID>")
      ("d,delete", "Delete todos by ID(s) (e.g., 1,2,3)", cxxopts::value<std::vector<unsigned int>>(), "<TODO_ID(s)>")
      ("l,list", "List all todos");

  options.add_options("Querying")
      ("t,title", "Set the title for add or update queries", cxxopts::value<std::string>(), "<TITLE>")
      ("p,priority", "Set priority (1: Low, 2: Medium, 3: High) for add or update queries", cxxopts::value<unsigned int>(), "<PRIORITY>")
      ("f,filter", "Filter todos by priorities for list queries (e.g., 1,2)", cxxopts::value<std::vector<unsigned int>>(), "<PRIORITIES>")
      ("s,search", "Search todos by words", cxxopts::value<std::string>(), "<WORDS>");

  options.add_options("General")
      ("v,version", "Show todocxx version")
      ("h,help", "Print help message");
  // clang-format on

  if (argc <= 1) {
    fmt::println(stderr, "{}", options.help());
    return 1;
  }

  // Get todo.txt path
  char path_sep = static_cast<std::string>(PLATFORM) == "windows" ? '\\' : '/';
  const char *home = static_cast<std::string>(PLATFORM) == "windows"
                         ? std::getenv("USERPROFILE")
                         : std::getenv("HOME");

  if (home == NULL) {
    fmt::println(stderr, "Sorry, todocxx does not support your platform!");
    return 1;
  }
  std::string data_path =
      static_cast<std::string>(home) + path_sep + "todo.txt";

  try {
    auto result = options.parse(argc, argv);

    if (result.count("help")) {
      fmt::println("{}", options.help());
      return 0;
    }

    if (result.count("version")) {
      fmt::println("{} version {}", app_name, app_version);
      return 0;
    }

    if (result.count("list")) {
      Csv file(data_path, std::ios::in);
      std::list<Todo> content = file.read_content();

      if (content.empty()) {
        fmt::print(fmt::emphasis::bold, "No data\n");
      } else {
        print_table(content);
      }

      return 0;
    }

    if (result.count("add")) {
      // TODO: handle add todo
    }

    if (result.count("delete")) {
      // TODO: handle delete todos
    }
  } catch (const cxxopts::exceptions::exception &e) {
    fmt::println(stderr, "Error parsing options: {}", e.what());
    fmt::println(stderr, "Use '--help' for more information.");
    return 1;
  }

  return 0;
}
