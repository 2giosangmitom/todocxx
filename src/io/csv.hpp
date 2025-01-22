#ifndef CSV_HPP
#define CSV_HPP

#include <fmt/core.h>

#include <fstream>
#include <list>
#include <string>

#include "../cli/todo.hpp"

class Csv {
 private:
  std::fstream file;
  std::string file_path;

 public:
  Csv(const std::string &path) : file_path{path} {
    // Open the file for reading and writing, create it if it doesn't exist
    file.open(file_path, std::ios::in | std::ios::out | std::ios::app);

    if (!file.is_open()) {
      fmt::println(stderr, "Failed to open file: {}", file_path);
    }
  }

  std::list<Todo> read_content() {
    std::string line;
    std::list<Todo> res;

    if (!file.is_open()) {
      fmt::println("File is not open for reading: {}", file_path);
      return res;
    }

    while (std::getline(file, line)) {
      if (line.empty()) continue;  // Skip empty lines

      std::uint8_t priority = line.back() - '0';
      std::string title = line.substr(0, line.size() - 2);

      // Validate priority
      if (priority < 1 || priority > 3) {
        fmt::println("Invalid priority value: {}", priority);
        priority = 0;  // Set to 0 for unknown
      }

      Todo t{static_cast<std::uint32_t>(res.size() + 1), title, priority};
      res.push_back(t);
    }

    return res;
  }

  ~Csv() {
    if (file.is_open()) {
      file.close();
    }
  }
};

#endif  // CSV_HPP
