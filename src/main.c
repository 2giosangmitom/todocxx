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

#include "project.h"
#include "services/storage.h"
#include "utils/fmt.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <uthash.h>

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
  printf("  %-25s %s\n", "<task>", "The task description (e.g., \"Learn C\")");
  printf("  %-25s %s\n", "<title>",
         "The heading for TODO.md (e.g., \"Planned features\")");
  printf("  %-25s %s\n", "<id>",
         "The task ID (e.g., the number from the task list)");

  puts("\n" STYLE_BOLD STYLE_UNDERLINE "Options:" STYLE_RESET);
  printf("  %-25s %s\n", "-f, --file <path>",
         "Specify a custom TODO.md file path (defaults to TODO.md in the "
         "current directory)");
  printf("  %-25s %s\n", "-h, --help", "Show this help message");
  printf("  %-25s %s\n", "-v, --version", "Display the program version");
}

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

void exec(arg **arguments, const char *path) {
  arg *current, *tmp;

  HASH_ITER(hh, *arguments, current, tmp) {
    if (strcmp(current->name, "init") == 0) {
      if (init(path, current->value)) {
        print_info("Initialized todos at %s", path);
      }
    }
  }
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
  bool file = false;
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
    // TODO: list all todo
  }

  if (clear) {
    // TODO: list all todo
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
