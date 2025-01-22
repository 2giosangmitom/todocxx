#ifndef CSV_HPP
#define CSV_HPP

#include "../cli/todo.hpp"
#include <fmt/core.h>
#include <fstream>
#include <ios>
#include <list>
#include <string>
#include <sys/types.h>

class Csv {
private:
  std::fstream file;
  std::string file_path;

public:
  Csv(const std::string &path, std::ios::openmode mode) : file_path{path} {
    file.open(file_path, mode | std::ios::app);

    if (!file) {
      fmt::println("Failed to open file: {}", file_path);
    }
  };

  std::list<Todo> read_content() {
    std::string line;
    std::list<Todo> res;

    for (u_int32_t i = 1; std::getline(file, line); i++) {
      u_int8_t priority = *(line.end() - 1) - '0';
      std::string title = line.substr(0, line.size() - 2);
      Todo t{i, title, priority};
      res.push_back(t);
    }

    return res;
  }

  ~Csv() { file.close(); };
};

#endif // !CSV_HPP
