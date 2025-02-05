/*
 * MIT License
 *
 * Copyright (c) 2025 Võ Quang Chiến
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uthash.h>
#include <utlist.h>

#include "project.h"
#include "services/storage.h"
#include "utils/fmt.h"

typedef struct {
  char *name; // key
  char *value;
  UT_hash_handle hh;
} arg;

// Print help message
void print_help(char *name) {
  puts(PROJECT_DESCRIPTION "\n");

  printf("%s: %s [COMMAND] [ARGUMENTS] [OPTIONS]\n\n",
         STYLE_BOLD STYLE_UNDERLINE "Usage" STYLE_RESET, name);

  puts(STYLE_BOLD STYLE_UNDERLINE "Commands:" STYLE_RESET);
  printf("  %-25s %s\n", "init <title>",
         "Create TODO.md in the current directory");
  printf("  %-25s %s\n", "add <task>", "Add a new task to TODO.md");
  printf("  %-25s %s\n", "list", "Display all tasks");
  printf("  %-25s %s\n", "done <id>",
         "Mark the task with ID <id> as completed");
  printf("  %-25s %s\n", "remove <id>", "Remove the task with ID <id>");
  printf("  %-25s %s\n", "clear", "Remove all tasks from TODO.md");

  puts("\n" STYLE_BOLD STYLE_UNDERLINE "Arguments:" STYLE_RESET);
  printf("  %-25s %s\n", "task", "The task description (e.g., \"Learn C\")");
  printf("  %-25s %s\n", "title",
         "The heading for TODO.md (e.g., \"Planned features\")");
  printf("  %-25s %s\n", "id...",
         "The task ID (e.g., the number from the task list)");

  puts("\n" STYLE_BOLD STYLE_UNDERLINE "Options:" STYLE_RESET);
  printf("  %-25s %s\n", "-f, --file <path>",
         "Specify a custom TODO.md file path (defaults to TODO.md in the "
         "current directory)");
  printf("  %-25s %s\n", "-h, --help", "Show this help message");
  printf("  %-25s %s\n", "-v, --version", "Display the program version");
}

// Add new argument to hash table
void add_argument(arg **arguments, char *name, char *value) {
  arg *new_arg;

  HASH_FIND_STR(*arguments, name, new_arg);

  if (new_arg == NULL) {
    new_arg = (arg *)malloc(sizeof(arg));
    new_arg->name = name;
    new_arg->value = value;
    HASH_ADD_STR(*arguments, name, new_arg);
  } else {
    new_arg->value = value;
  }
}

// Release hash table memory
void hash_release(arg **arguments) {
  if (arguments == NULL) {
    return;
  }

  arg *current, *tmp;

  HASH_ITER(hh, *arguments, current, tmp) {
    HASH_DEL(*arguments, current);
    free(current);
  }
}

uint32_t *parse_ids(const char *val, int *returnSize) {
  uint32_t *ids = NULL;
  int count = 0;

  char buffer[1024];
  size_t j = 0;

  for (size_t i = 0; i <= strlen(val); i++) {
    if (isdigit(val[i])) {
      continue;
    }

    if (val[i] == ',' || val[i] == '\0') {
      if (i == j) { // Consecutive commas or empty number
        print_err("Invalid syntax (empty number between commas).");
        returnSize = 0;
        free(ids);
        return NULL;
      }
      size_t num_len = i - j;
      if (num_len >= sizeof(buffer)) {
        print_err("Number too large.");
        returnSize = 0;
        free(ids);
        return NULL;
      }
      strncpy(buffer, val + j, num_len);
      buffer[num_len] = '\0';
      j = i + 1;
      ids = realloc(ids, sizeof(int) * (count + 1));
      ids[count++] = atoi(buffer);
    } else {
      print_err("Invalid character in argument.");
      returnSize = 0;
      free(ids);
      return NULL;
    }
  }

  *returnSize = count;
  return ids;
}

void exec(arg **arguments, const char *path) {
  arg *current, *tmp;

  HASH_ITER(hh, *arguments, current, tmp) {
    if (strcmp(current->name, "init") == 0) {
      if (init(path, current->value)) {
        print_info("Initialized todos at %s", path);
      }
    } else if (strcmp(current->name, "add") == 0) {
      if (add_todo(path, current->value, false)) {
        print_info("Added '%s' task to %s", current->value, path);
      }
    } else { // remove or done command
      char *val = current->value;

      int returnSize;
      uint32_t *ids = parse_ids(val, &returnSize);
      struct TodoNode *todos = list_todos(path);
      struct TodoNode *elt, *tmp;

      if (!ids || !todos) {
        break;
      }

      for (int i = 0; i < returnSize; i++) {
        DL_FOREACH_SAFE(todos, elt, tmp) {
          if (elt->todo.id == ids[i]) {
            if (strcmp(current->name, "done") == 0) {
              elt->todo.is_done = true;
            } else {
              DL_DELETE(todos, elt);
              free(elt);
            }
          }
        }
      }

      if (write_todos(todos, path)) {
        print_info("Updated %s", path);
      }

      free_list(todos);
      free(ids);
    }
  }
}

int get_num_digits(int num) { return snprintf(NULL, 0, "%d", num); }

int max(int n, int m) {
  if (n < m) {
    return m;
  }
  return n;
}

void print_line(char *c1, char *c2, char *c3, int c1_w, int c2_w, int c3_w) {
  printf("%s", c1); // Left corner
  for (int i = 0; i < c1_w; i++)
    printf("%s", H_LINE);
  printf("%s", c2);
  for (int i = 0; i < c2_w; i++)
    printf("%s", H_LINE);
  printf("%s", c2);
  for (int i = 0; i < c3_w; i++)
    printf("%s", H_LINE);
  printf("%s\n", c3); // Right corner
}

void print_data(int c1, char *c2, bool c3, int c1_w, int c2_w, int c3_w) {
  printf(V_LINE);
  printf(" %d%*s", c1, c1_w - get_num_digits(c1) - 1, "");
  printf(V_LINE);
  printf(" %s%*s", c2, c2_w - (int)strlen(c2) - 1, "");
  printf(V_LINE);
  printf(" %s%*s",
         c3 ? COLOR_GREEN CHECK_MARK STYLE_RESET
            : COLOR_RED CROSS_MARK STYLE_RESET,
         c3_w - 2, "");
  printf(V_LINE);
  printf("\n");
}

void print_todos(struct TodoNode *head) {
  int c1_w = 3; // #
  int c2_w = 6; // Task
  int c3_w = 6; // Done

  struct TodoNode *elt, *tmp;
  DL_FOREACH_SAFE(head, elt, tmp) {
    c1_w = max(get_num_digits(elt->todo.id) + 2, c1_w);
    c2_w = max(c2_w, strlen(elt->todo.content) + 2);
  }

  // Print the top border
  print_line(TOP_LEFT, TOP_MID, TOP_RIGHT, c1_w, c2_w, c3_w);

  // Print heading
  printf("%s %s", V_LINE, STYLE_BOLD "#" STYLE_RESET);
  printf("%*s", c1_w - 2, "");
  printf(V_LINE);
  printf(" %s%*s", STYLE_BOLD "Task" STYLE_RESET, c2_w - 5, "");
  printf(V_LINE);
  printf(" %s%*s", STYLE_BOLD "Done" STYLE_RESET, c3_w - 5, "");
  printf(V_LINE);
  printf("\n");

  // Print middle separator
  print_line(LEFT_MID, CROSS, RIGHT_MID, c1_w, c2_w, c3_w);

  // Print table data
  DL_FOREACH_SAFE(head, elt, tmp) {
    print_data(elt->todo.id, elt->todo.content, elt->todo.is_done, c1_w, c2_w,
               c3_w);
  }

  // Print bottom border
  print_line(BOTTOM_LEFT, BOTTOM_MID, BOTTOM_RIGHT, c1_w, c2_w, c3_w);
}

int main(int argc, char **argv) {
  if (argc <= 1) {
    print_err("Expect a command. See '--help' for details.");
    return EXIT_FAILURE;
  }

  // Parse arguments
  arg *arguments = NULL;

  bool help = false;
  bool version = false;
  char *file_path = "TODO.md";
  bool list = false;
  bool clear = false;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
      help = true;
    } else if (strcmp(argv[i], "--version") == 0 ||
               strcmp(argv[i], "-v") == 0) {
      version = true;
    } else if (strcmp(argv[i], "--file") == 0 || strcmp(argv[i], "-f") == 0) {
      i++; // Move to next arg
      file_path = argv[i];
    } else if (strcmp(argv[i], "init") == 0 && i < argc - 1) {
      i++; // Move to next arg
      add_argument(&arguments, argv[i - 1], argv[i]);
    } else if (strcmp(argv[i], "add") == 0 && i < argc - 1) {
      i++; // Move to next arg
      add_argument(&arguments, argv[i - 1], argv[i]);
    } else if (strcmp(argv[i], "list") == 0) {
      list = true;
    } else if (strcmp(argv[i], "done") == 0 && i < argc - 1) {
      i++; // Move to next arg
      add_argument(&arguments, argv[i - 1], argv[i]);
    } else if (strcmp(argv[i], "remove") == 0 && i < argc - 1) {
      i++; // Move to next arg
      add_argument(&arguments, argv[i - 1], argv[i]);
    } else if (strcmp(argv[i], "clear") == 0) {
      clear = true;
    } else {
      print_err("Invalid arguments. See '--help' for details.");
      hash_release(&arguments);
      return EXIT_FAILURE;
    }
  }

  exec(&arguments, file_path);

  if (list) {
    struct TodoNode *head = list_todos(file_path);
    if (!head && !errno) {
      print_info("No task in %s. Yeah!", file_path);
    }

    if (head) {
      print_todos(head);
      free_list(head);
    }
  }

  if (clear) {
    if (write_todos(NULL, file_path)) {
      print_info("Updated %s", file_path);
    }
  }

  if (help) {
    print_help(argv[0]);
    hash_release(&arguments);
    return EXIT_SUCCESS;
  }

  if (version) {
    printf("%s version %s\n", argv[0], PROJECT_VERSION);
    hash_release(&arguments);
    return EXIT_SUCCESS;
  }

  hash_release(&arguments);
  return EXIT_SUCCESS;
}
