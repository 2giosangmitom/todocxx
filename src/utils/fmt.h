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

#ifndef FMT_H
#define FMT_H

// Foreground colors
#define COLOR_BLACK "\033[0;30m"
#define COLOR_RED "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_MAGENTA "\033[0;35m"
#define COLOR_CYAN "\033[0;36m"
#define COLOR_WHITE "\033[0;37m"

// Background colors
#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

// Text styles
#define STYLE_BOLD "\033[1m"
#define STYLE_UNDERLINE "\033[4m"
#define STYLE_RESET "\033[0m" // Reset style and color

// Unicode character
#define CHECK_MARK "\xe2\x9c\x93"  // ✓
#define CROSS_MARK "\xe2\x9c\x97"  // ✗
#define H_LINE "\xe2\x94\x80"       // ─
#define V_LINE "\xe2\x94\x82"       // │
#define TOP_LEFT "\xe2\x94\x8c"     // ┌
#define TOP_RIGHT "\xe2\x94\x90"    // ┐
#define BOTTOM_LEFT "\xe2\x94\x94"  // └
#define BOTTOM_RIGHT "\xe2\x94\x98" // ┘
#define TOP_MID "\xe2\x94\xac"      // ┬
#define BOTTOM_MID "\xe2\x94\xb4"   // ┴
#define LEFT_MID "\xe2\x94\x9c"     // ├
#define RIGHT_MID "\xe2\x94\xa4"    // ┤
#define CROSS "\xe2\x94\xbc"        // ┼

// Print error message to stderr
void print_err(const char *message);

// Print info message
void print_info(const char *format, ...);

#endif
