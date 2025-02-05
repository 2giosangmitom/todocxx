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

#ifndef STORAGE_H
#define STORAGE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
  uint32_t id;
  char content[1024];
  bool is_done;
} Todo;

struct TodoNode {
  Todo todo;
  struct TodoNode *next;
  struct TodoNode *prev;
};

// Init the TODO.md or other name if user want ._.
bool init(const char *file_path, const char *title);

// Get all todos, return the pointer to head of linked list
struct TodoNode *list_todos(const char *file_path);

// Release memory of todo list
void free_list(struct TodoNode *head);

// Add todo to file
bool add_todo(const char *file_path, const char *task, bool is_done);

// Check the file if exist
bool _file_exist(const char *file_path);

// Ensure the file ends with a newline
void _ensure_newline(FILE *file);

// Mark a task as done
bool done_task(const char *file_path, int id);

// Write new data to file
bool write_todos(struct TodoNode *head, const char *file_path);

#endif
