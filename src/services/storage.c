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

#include "storage.h"
#include "../utils/fmt.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utlist.h>

// Init the TODO.md or other name if user want ._.
bool init(const char *file_path, const char *title) {
  FILE *file = fopen(file_path, "w");
  if (!file) {
    print_err(strerror(errno));
    return false;
  }

  if (strlen(title) != 0) {
    fprintf(file,
            "<!-- Modify if you want to update the content or unmark ._. "
            "-->\n# %s\n\n",
            title);
  } else {
    fprintf(
        file,
        "<!-- Modify if you want to update the content or unmark ._. -->\n");
  }

  fclose(file);
  return true;
}

// Get all todos, return the pointer to head of linked list
struct TodoNode *list_todos(const char *file_path) {
  FILE *file = fopen(file_path, "r");
  if (!file) {
    print_err(strerror(errno));
    return NULL;
  }

  struct TodoNode *res = NULL;
  char buffer[1024];
  int i = 0;

  while (fgets(buffer, sizeof(buffer), file)) {
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline if exist

    struct TodoNode *new_node =
        (struct TodoNode *)malloc(sizeof(struct TodoNode));
    if (!new_node) {
      print_err("Memory allocation failed");
      fclose(file);
      free_list(res);
      return NULL;
    }

    // Parse string
    int j = 0;
    while (buffer[j] == ' ') { // Skip leading spaces
      j++;
    }

    if (buffer[j] != '-') { // Invalid format for todo in markdown
      free(new_node);
      continue;
    }

    // Get status
    j += 2;
    if (buffer[j] != '[') {
      free(new_node);
      continue;
    }
    j++;
    if (buffer[j] == ' ') {
      new_node->todo.is_done = false;
    } else {
      new_node->todo.is_done = true;
    }
    j++;
    if (buffer[j] != ']') {
      free(new_node);
      continue;
    }

    j++;
    while (buffer[j] == ' ') {
      j++;
    }
    strcpy(new_node->todo.content, buffer + j);
    new_node->todo.id = ++i;

    DL_APPEND(res, new_node);
  }

  fclose(file);
  return res;
}

// Release memory of todo list
void free_list(struct TodoNode *head) {
  struct TodoNode *elt, *tmp;
  DL_FOREACH_SAFE(head, elt, tmp) { free(elt); }
}
