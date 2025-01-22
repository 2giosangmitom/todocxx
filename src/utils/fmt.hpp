#ifndef FMT_HPP
#define FMT_HPP

#include <fmt/color.h>
#include <fmt/core.h>

// Print error message
inline void print_error(const std::string_view &message) {
  fmt::println(stderr, "{}: {}",
               fmt::styled("[ERROR]", fmt::fg(fmt::color::light_coral)),
               message);
}

// Print info message
inline void print_info(const std::string_view &message) {
  fmt::println("{}: {}", fmt::styled("[INFO]", fmt::fg(fmt::color::cyan)),
               message);
}

#endif
