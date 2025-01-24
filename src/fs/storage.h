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

#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <fmt/core.h>

#include <cstdint>
#include <fstream>
#include <list>
#include <sstream>
#include <string>

#include "../model.h"
#include "../utils/fmt.h"

class Storage {
 private:
  std::string file_path;

 public:
  Storage(const std::string &path) : file_path{path} {}

  std::list<Todo> read_todos() {
    std::ifstream file(file_path, std::ios::in | std::ios::binary);
    std::string line;
    std::list<Todo> res;

    if (!file.is_open()) {
      print_error("Failed to open file for reading: " + file_path);
      return res;  // Return empty list
    }

    while (std::getline(file, line)) {
      if (line.empty()) continue;  // Skip empty lines

      std::istringstream iss(line);
      std::string title;
      uint32_t priority;

      if (std::getline(iss, title, '|') && iss >> priority) {
        if (priority < 1 || priority > 3) {
          priority = 0;  // Set to 0 for unknown
        }
        Todo t{uint32_t(res.size() + 1), title, priority};
        res.push_back(t);
      }
    }

    return res;
  }

  void add_todo(const std::string &title, const uint32_t &priority) {
    std::ofstream file(file_path,
                       std::ios::out | std::ios::app | std::ios::binary);

    if (!file.is_open()) {
      print_error("Failed to open file for appending: " + file_path);
      return;
    }

    file << title << "|" << priority << std::endl;
  }

  void write_todos(const std::list<Todo> &new_todos) {
    std::ofstream file(file_path,
                       std::ios::out | std::ios::trunc | std::ios::binary);

    if (!file.is_open()) {
      print_error("Failed to open file for writing: " + file_path);
      return;
    }

    for (const Todo &t : new_todos) {
      file << t.title << "|" << t.priority << std::endl;
    }
  }
};

#endif  // STORAGE_HPP
