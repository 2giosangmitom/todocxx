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
#include "utils/fmt.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <uthash.h>

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

int main(int argc, char **argv) {
  if (argc <= 1) {
    print_err("Expect a command. See '--help' for details.");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
