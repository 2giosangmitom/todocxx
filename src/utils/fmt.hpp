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

#endif