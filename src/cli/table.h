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

#ifndef TABLE_HPP
#define TABLE_HPP

#include <fmt/color.h>
#include <fmt/core.h>

#include <algorithm>
#include <array>
#include <list>
#include <string>

#include "../model.h"

constexpr size_t kDefaultTitleWidth = 7;
constexpr size_t kPriorityWidth = 10;

inline void print_border(const std::array<size_t, 3>& col_wids) {
  for (const auto& wid : col_wids) {
    fmt::print("+{}", std::string(wid, '-'));
  }
  fmt::println("+");
}

inline void print_row(const Todo& todo, const std::array<size_t, 3>& col_wids) {
  std::string_view priority;
  fmt::color priority_color;

  switch (todo.priority) {
    case 1:
      priority = "Low";
      priority_color = fmt::color::light_green;
      break;
    case 2:
      priority = "Medium";
      priority_color = fmt::color::yellow;
      break;
    case 3:
      priority = "High";
      priority_color = fmt::color::coral;
      break;
    default:
      priority = "Unknown";  // Handle unexpected priorities
      priority_color = fmt::color::aquamarine;
      break;
  }

  fmt::println(
      "| {}{} | {}{} | {}{} |", todo.id,
      std::string(col_wids[0] - 2 - std::to_string(todo.id).size(), ' '),
      todo.title, std::string(col_wids[1] - 2 - todo.title.size(), ' '),
      fmt::styled(priority, fmt::fg(priority_color)),
      std::string(col_wids[2] - 2 - priority.size(), ' '));
}

inline void print_table(const std::list<Todo>& content) {
  const size_t fcol_wid = std::max(std::to_string(content.size()).size() + 2,
                                   static_cast<size_t>(4));
  size_t crcol_wid = kDefaultTitleWidth;

  // Calculate the maximum width for the title column
  for (const auto& todo : content) {
    crcol_wid = std::max(todo.title.size() + 2, crcol_wid);
  }

  std::array<size_t, 3> col_wids = {fcol_wid, crcol_wid, kPriorityWidth};

  print_border(col_wids);

  fmt::println(
      "| {}{} | {}{} | {} |",
      fmt::styled("ID", fmt::emphasis::bold | fmt::emphasis::underline),
      std::string(fcol_wid - 4, ' '),
      fmt::styled("Title", fmt::emphasis::bold | fmt::emphasis::underline),
      std::string(crcol_wid - kDefaultTitleWidth, ' '),
      fmt::styled("Priority", fmt::emphasis::bold | fmt::emphasis::underline));
  print_border(col_wids);

  for (const auto& todo : content) {
    print_row(todo, col_wids);
  }

  print_border(col_wids);
}

#endif  // TABLE_HPP
