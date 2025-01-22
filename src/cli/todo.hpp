#ifndef TODO_HPP
#define TODO_HPP

#include <cstdint>
#include <string>

struct Todo {
  uint32_t id;
  std::string title;
  uint8_t priority;
};

#endif  // !TODO_HPP
