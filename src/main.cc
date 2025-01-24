/*
 * MIT License
 *
 * Copyright (c) 2025 Võ Quang Chiến
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <fmt/color.h>
#include <fmt/core.h>

#include <cstdint>
#include <cxxopts.hpp>
#include <list>
#include <optional>
#include <regex>
#include <string>
#include <vector>

#include "cli/table.h"
#include "fs/storage.h"
#include "utils/fmt.h"

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
  const char* home =
      std::getenv(std::string(PLATFORM) == "windows" ? "USERPROFILE" : "HOME");
  return home ? std::optional<std::string>(home) : std::nullopt;
}

void print_help(const cxxopts::Options& options) {
  fmt::println("{}", options.help());
}

void print_version(const std::string& app_name,
                   const std::string& app_version) {
  fmt::println("{} version {}", app_name, app_version);
}

void list_todos(const std::string& data_path) {
  Storage file(data_path);
  std::list<Todo> content = file.read_todos();

  if (content.empty()) {
    fmt::print(fmt::emphasis::bold, "No data\n");
  } else {
    print_table(content);
  }
}

void add_todo(const std::string& data_path, const std::string& title,
              uint32_t priority) {
  Storage file(data_path);
  file.add_todo(title, priority);
}

void delete_todos(const std::string& data_path,
                  const std::vector<uint32_t>& ids) {
  Storage file(data_path);
  std::list<Todo> todos = file.read_todos();

  for (const uint32_t& id : ids) {
    todos.remove_if([id](const Todo& t) { return t.id == id; });
  }

  file.write_todos(todos);
}

void update_todo(const std::string& data_path, uint32_t id,
                 const std::string& title, std::optional<uint32_t> priority) {
  Storage file(data_path);
  std::list<Todo> todos = file.read_todos();

  for (Todo& t : todos) {
    if (t.id == id) {
      t.title = title;
      if (priority) {
        t.priority = *priority;
      }
    }
  }

  file.write_todos(todos);
}

void filter_todos(const std::string& data_path,
                  const std::vector<uint32_t>& priorities) {
  Storage file(data_path);
  std::list<Todo> todos = file.read_todos();
  std::list<Todo> filtered_todos;

  for (const auto& t : todos) {
    if (std::find(priorities.begin(), priorities.end(), t.priority) !=
        priorities.end()) {
      filtered_todos.push_back(t);
    }
  }

  print_table(filtered_todos);
}

void search_todos(const std::string& data_path, const std::string& pattern) {
  std::string trimmed_pattern = pattern;
  trimmed_pattern.erase(0, trimmed_pattern.find_first_not_of(" "));
  trimmed_pattern.erase(trimmed_pattern.find_last_not_of(" ") + 1);

  trimmed_pattern = std::regex_replace(
      trimmed_pattern, std::regex(R"([.^$|()\\[*+?{}])"), R"(\$&)");

  if (trimmed_pattern.empty()) {
    print_error("Search pattern is empty!");
    return;
  }

  Storage file(data_path);
  std::list<Todo> todos = file.read_todos();

  std::regex regex_pattern(trimmed_pattern, std::regex_constants::icase);

  todos.remove_if([&regex_pattern](const Todo& t) {
    return !std::regex_search(t.title, regex_pattern);
  });

  print_table(todos);
}

int main(int argc, char* argv[]) {
  const std::string app_version = "v1.0.2";
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
  const char path_sep = (std::string(PLATFORM) == "windows") ? '\\' : '/';
  const auto home_dir = get_home_directory();

  if (!home_dir) {
    print_error("Sorry, todocxx does not support your platform!");
    return 1;
  }

  const std::string data_path = *home_dir + path_sep + "todo.txt";

  try {
    const auto result = options.parse(argc, argv);

    if (result.count("help")) {
      print_help(options);
      return 0;
    }

    if (result.count("version")) {
      print_version(app_name, app_version);
      return 0;
    }

    if (result.count("list")) {
      list_todos(data_path);
      return 0;
    }

    if (result.count("add")) {
      if (!result.count("priority")) {
        print_error("You must provide a priority with --priority");
        return 1;
      }

      const uint32_t priority = result["priority"].as<uint32_t>();
      const std::string title = result["add"].as<std::string>();

      add_todo(data_path, title, priority);
      return 0;
    }

    if (result.count("delete")) {
      const auto ids = result["delete"].as<std::vector<uint32_t>>();
      delete_todos(data_path, ids);
      return 0;
    }

    if (result.count("update")) {
      if (!result.count("title")) {
        print_error("You must provide a title with --title");
        return 1;
      }

      const uint32_t id = result["update"].as<uint32_t>();
      const std::string title = result["title"].as<std::string>();
      const std::optional<uint32_t> priority =
          result.count("priority")
              ? std::optional<uint32_t>(result["priority"].as<uint32_t>())
              : std::nullopt;

      update_todo(data_path, id, title, priority);
      return 0;
    }

    if (result.count("filter")) {
      const auto priorities = result["filter"].as<std::vector<uint32_t>>();
      filter_todos(data_path, priorities);
      return 0;
    }

    if (result.count("search")) {
      const std::string pattern = result["search"].as<std::string>();
      search_todos(data_path, pattern);
      return 0;
    }
  } catch (const cxxopts::exceptions::exception& e) {
    print_error(e.what());
    print_info("Use '--help' for more information");
    return 1;
  }

  return 0;
}
