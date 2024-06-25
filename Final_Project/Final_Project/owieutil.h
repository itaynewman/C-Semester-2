#ifndef OWIEUTIL_H
#define OWIEUTIL_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#endif

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#ifdef _WIN32
#include <conio.h>
#include <Windows.h>
#include <shlobj.h>
#include <commdlg.h>
#else
#include <unistd.h>
#include <termios.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

#define ANSIC_RESET "\x1b[0m"
#define ANSIC_WHITE "\x1b[38;2;255;255;255m"
#define ANSIC_GRAY "\x1b[38;2;68;68;68m"
#define ANSIC_PURPLE_DOT "\x1b[38;2;215;95;215m"
#define ANSIC_PURPLE "\x1b[38;2;135;95;135m"
#define ANSIC_PURPLE_BRIGHT "\x1b[1;38;2;215;175;255m"
#define ANSIC_RED_DOT "\x1b[38;2;255;95;95m"
#define ANSIC_RED "\x1b[38;2;135;95;95m"
#define ANSIC_RED_BRIGHT "\x1b[1;38;2;255;175;175m"
#define ANSIC_GOLD_DOT "\x1b[38;2;215;135;0m"
#define ANSIC_GOLD "\x1b[38;2;135;95;0m"
#define ANSIC_GOLD_BRIGHT "\x1b[1;38;2;215;175;0m"
#define ANSIC_GREEN_DOT "\x1b[38;2;175;215;135m"
#define ANSIC_GREEN "\x1b[38;2;175;175;95m"
#define ANSIC_GREEN_BRIGHT "\x1b[1;38;2;175;215;135m"
#define ANSIC_BLUE_DOT "\x1b[38;2;135;175;215m"
#define ANSIC_BLUE "\x1b[38;2;135;175;135m"
#define ANSIC_BLUE_BRIGHT "\x1b[1;38;2;175;215;135m"
#define ANSIC_COLOR_RED "\x1b[31m"
#define ANSIC_COLOR_GREEN "\x1b[32m"
#define ANSIC_COLOR_YELLOW "\x1b[33m"
#define ANSIC_COLOR_BLUE "\x1b[34m"
#define ANSIC_COLOR_MAGENTA "\x1b[35m"
#define ANSIC_COLOR_CYAN "\x1b[36m"
#define ANSIC_COLOR_RESET "\x1b[0m"

void nprint_full(const char* style, const char* text, bool clock, const char* end, FILE* file, ...);
#define nprint(style, text, ...) nprint_full(style, text, false, NULL, NULL, ##__VA_ARGS__)
#define nprint_clock(style, text, ...) nprint_full(style, text, true, NULL, NULL, ##__VA_ARGS__)
const char* npicker(const char* style, const char* title, const char** options, int num_options);
void ninput(const char* style, const char* prompt, char* buffer, size_t buffer_size);

#endif // OWIEUTIL_H
