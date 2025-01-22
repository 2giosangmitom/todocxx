#ifndef TABLE_HPP
#define TABLE_HPP

#include "../cli/todo.hpp"
#include <fmt/color.h>
#include <fmt/core.h>
#include <initializer_list>
#include <list>
#include <vector>

inline void print_border(const std::initializer_list<size_t> &col_wids) {
  for (const auto &wid : col_wids) {
    fmt::print("+{}", std::string(wid, '-'));
  }
  fmt::println("+");
}

inline void print_row(const Todo &t, const std::vector<size_t> &col_wids) {
  fmt::println("| {}{} | {}{} | {}{} |", t.id,
               std::string(col_wids[0] - 2 - std::to_string(t.id).size(), ' '),
               t.title, std::string(col_wids[1] - 2 - t.title.size(), ' '),
               t.id == 1   ? "Low"
               : t.id == 2 ? "Medium"
                           : "High",
               std::string(col_wids[2] - (t.id == 1   ? 5
                                          : t.id == 2 ? 8
                                                      : 6),
                           ' '));
}

inline void print_table(const std::list<Todo> &content) {
  const size_t fcol_wid = std::max(content.size() + 2, static_cast<size_t>(4));
  size_t crcol_wid = 0;
  const size_t lcol_wid = 10;

  for (Todo t : content) {
    crcol_wid = std::max(t.title.size() + 2, crcol_wid);
  }
  crcol_wid = std::max(crcol_wid, static_cast<size_t>(5));

  print_border({fcol_wid, crcol_wid, lcol_wid});

  fmt::println(
      "| {}{} | {}{} | {} |",
      fmt::styled("ID", fmt::emphasis::bold | fmt::emphasis::underline),
      std::string(fcol_wid - 4, ' '),
      fmt::styled("Title", fmt::emphasis::bold | fmt::emphasis::underline),
      std::string(crcol_wid - 7, ' '),
      fmt::styled("Priority", fmt::emphasis::bold | fmt::emphasis::underline));
  print_border({fcol_wid, crcol_wid, lcol_wid});

  for (Todo t : content) {
    print_row(t, {fcol_wid, crcol_wid, lcol_wid});
  }

  print_border({fcol_wid, crcol_wid, lcol_wid});
}

#endif // !TABLE_HPP
