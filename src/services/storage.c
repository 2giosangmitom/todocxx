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
#include <string.h>

// Init the TODO.md or other name if user want ._.
bool init(const char *file_path, const char *title) {
  FILE *file = fopen(file_path, "w");
  if (!file) {
    print_err(strerror(errno));
    return false;
  }

  if (strlen(title) != 0) {
    fprintf(file,
            "<!-- Modify if you want to update ._. (Not implemented feature) "
            "-->\n# %s\n\n",
            title);
  } else {
    fprintf(file, "<!-- Modify if you want to update ._. (Not implemented "
                  "feature) -->\n");
  }

  fclose(file);
  return true;
}
