#ifndef TODO_HPP
#define TODO_HPP

#include <sys/types.h>

#include <string>

struct Todo {
  u_int32_t id;
  std::string title;
  u_int8_t priority;
};

#endif  // !TODO_HPP
