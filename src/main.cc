#include <fmt/color.h>
#include <fmt/core.h>

#include <cxxopts.hpp>
#include <list>
#include <optional>
#include <string>
#include <vector>

#include "cli/table.hpp"
#include "io/storage.hpp"
#include "utils/fmt.hpp"

// Check platform
#if defined(_WIN32)
#define PLATFORM "windows"
#elif defined(__linux__)
#define PLATFORM "linux"
#elif defined(__APPLE__)
#define PLATFORM "macos"
#endif

// Valid priorities
enum class Priority { Low = 1, Medium, High };

// Get the home directory or data file on windows
std::optional<std::string> get_home_directory() {
  const char *home =
      std::getenv(std::string(PLATFORM) == "windows" ? "USERPROFILE" : "HOME");
  return home ? std::optional<std::string>(home) : std::nullopt;
}

int main(int argc, char *argv[]) {
  const std::string app_version = "1.0.0";
  const std::string app_name = "todocxx";
  const std::string app_desc =
      "A blazing-fast CLI tool to efficiently manage your todos directly from "
      "the terminal";

  cxxopts::Options options(app_name, app_desc);
  options.set_tab_expansion().set_width(100);

  // clang-format off
  options.add_options()
      ("a,add", "Add a new todo with a title", cxxopts::value<std::string>(), "<TITLE>")
      ("u,update", "Update a todo by ID", cxxopts::value<uint32_t>(), "<TODO_ID>")
      ("d,delete", "Delete todos by ID(s) (e.g., 1,2,3)", cxxopts::value<std::vector<uint32_t>>(), "<TODO_ID(s)>")
      ("l,list", "List all todos")
      ("t,title", "Set the title for add or update queries", cxxopts::value<std::string>(), "<TITLE>")
      ("p,priority", "Set priority (1: Low, 2: Medium, 3: High) for add or update queries", cxxopts::value<uint32_t>(), "<PRIORITY>")
      ("f,filter", "Filter todos by priorities for list queries (e.g., 1,2)", cxxopts::value<std::vector<uint32_t>>(), "<PRIORITIES>")
      ("s,search", "Search todos by words", cxxopts::value<std::string>(), "<WORDS>")
      ("v,version", "Show todocxx version")
      ("h,help", "Print help message");
  // clang-format on

  if (argc <= 1) {
    print_error("Arguments are required. See --help for more.");
    return 1;
  }

  // Get todo.txt path
  char path_sep = (std::string(PLATFORM) == "windows") ? '\\' : '/';
  auto home_dir = get_home_directory();

  if (!home_dir) {
    print_error("Sorry, todocxx does not support your platform!");
    return 1;
  }

  std::string data_path = *home_dir + path_sep + "todo.txt";

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
      Storage file(data_path);
      std::list<Todo> content = file.read_todos();

      if (content.empty()) {
        fmt::print(fmt::emphasis::bold, "No data\n");
      } else {
        print_table(content);
      }

      return 0;
    }

    if (result.count("add")) {
      if (!result.count("priority")) {
        print_error("You must provide a priority with --priority");
        return 1;
      }

      uint32_t priority = result["priority"].as<uint32_t>();
      std::string title = result["add"].as<std::string>();

      Storage file(data_path);
      file.add_todo(title, priority);

      return 0;
    }

    if (result.count("delete")) {
      // TODO: handle delete todos
    }

    if (result.count("update")) {
      // TODO: handle delete todos
    }

    if (result.count("filter")) {
      // TODO: handle delete todos
    }

    if (result.count("search")) {
      // TODO: handle delete todos
    }
  } catch (const cxxopts::exceptions::exception &e) {
    print_error(fmt::format("Error parsing options: {}", e.what()));
    print_error("Use '--help' for more information.");
    return 1;
  }

  return 0;
}
