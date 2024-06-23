#ifndef OWIEUTIL_H
#define OWIEUTIL_H

// Visual Studio CRT Security Warnings Disable
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#endif

// include all the necesary header files for input/output and other stuff we need
#include <stdio.h>  // for standard input/output operations
#include <stdbool.h>  // for boolean type
#include <string.h>  // for string manipulation functions
#include <stdlib.h>  // for memory allocation and other utility functions
#include <time.h>  // for time-related functions
#include <stdarg.h>  // for variable argument lists
#ifdef _WIN32
// windows-specific headers for console and file dialogs
#include <conio.h>  // for console input/output
#include <Windows.h>  // for windows api functions
#include <shlobj.h>  // for shell-related functions
#include <commdlg.h>  // for common dialog box interfaces
#else
// unix-like system headers for terminal control and file operations
#include <unistd.h>  // for unix standard functions
#include <termios.h>  // for terminal control
#include <limits.h>  // for system limits
#include <fcntl.h>  // for file control options
#include <sys/types.h>  // for system types
#include <sys/stat.h>  // for file status
#endif

/**
 * @file owieutil.h
 * @brief utility functions for fancy console output and user input
 */

/**
 * @brief ansi color codes for making text look pretty in terminal
 * these are escape sequences that change text color
 */
// reset color to default
#define ANSIC_RESET "\x1b[0m"
// difrent color codes for text, each one sets a specific color
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

/**
 * @brief applies the choosen style to the text
 * this function sets up the colors for different text styles
 * 
 * @param style the style to use (like "info", "error", "warn", etc)
 * @param prefix pointer to store the prefix string
 * @param dot_color pointer to store the dot color
 * @param text_color pointer to store the text color
 * @param bright_color pointer to store the bright color
 */
static void apply_style(const char* style, const char** prefix, const char** dot_color, const char** text_color, const char** bright_color);

/**
 * @brief formats the text with cool colors
 * this function adds color codes to the text to make it look fancy
 * 
 * @param text the text to make pretty
 * @param text_color the color for normal text
 * @param bright_color the color for bold text
 * @return char* formatted text string with colors
 */
static char* format_text(const char* text, const char* text_color, const char* bright_color);

/**
 * @brief prints fancy text with optional styling, timestamp, and variable arguments
 * this function is the main workhorse for printing styled text to the console
 *
 * @param style the style of the text (like "info", "error", "warn", etc)
 * @param text the text to print (can have format specifiers)
 * @param clock if true, adds a timestamp to the output
 * @param end the string to put at the end (default is newline)
 * @param file the file to write to (default is stdout)
 * @param ... variable arguments to format into the text
 *
 * @example
 * // print an info message
 * nprint_full("info", "this is an [bold]info[/bold] message", false, NULL, NULL);
 * 
 * // print an error message with timestamp
 * nprint_full("error", "an [bold]error[/bold] occured: %s", true, NULL, NULL, "file not found");
 * 
 * // print a warning to a file
 * FILE* log_file = fopen("log.txt", "a");
 * nprint_full("warn", "warning: [bold]low disk space[/bold]", false, "\n\n", log_file);
 * fclose(log_file);
 */
void nprint_full(const char* style, const char* text, bool clock, const char* end, FILE* file, ...);

/**
 * @brief shortcut macro for nprint_full without clock and custom end/file
 * this macro makes it easier to use nprint_full for simple cases
 *
 * @example
 * // print a simple info message
 * nprint("info", "hello, world!");
 *
 * // print a formatted error message
 * nprint("error", "error code: [bold]%d[/bold]", 404);
 *
 * // print a success message with bold text
 * nprint("success", "operation [bold]completed[/bold] successfully");
 */
#define nprint(style, text, ...) nprint_full(style, text, false, NULL, NULL, ##__VA_ARGS__)

/**
 * @brief shortcut macro for nprint_full with clock but without custom end/file
 * this macro is useful when you want to include a timestamp in your output
 */
#define nprint_clock(style, text, ...) nprint_full(style, text, true, NULL, NULL, ##__VA_ARGS__)

/**
 * @brief shows a list of options and lets user pick with arrow keys
 * this function creates an interactive menu in the console
 *
 * @param style the style to use for the menu ("info", "error", "warn", etc)
 * @param title the title of the selection menu
 * @param options an array of strings with the options
 * @param num_options the number of options in the array
 * @return the selected option as a string
 *
 * @example
 * const char* options[] = {"option 1", "option 2", "option 3"};
 * const char* selected = npicker("info", "choose an option", options, 3);
 * printf("you selected: %s\n", selected);
 *
 * @example
 * const char* colors[] = {"red", "green", "blue", "yellow"};
 * const char* chosen_color = npicker("purple", "select your favorite color", colors, 4);
 * nprint("success", "you chose [bold]%s[/bold]!", chosen_color);
 *
 * @example
 * const char* difficulty_levels[] = {"easy", "medium", "hard", "extreme"};
 * const char* selected_difficulty = npicker("warn", "select difficulty level", difficulty_levels, 4);
 * nprint("info", "game difficulty set to: [bold]%s[/bold]", selected_difficulty);
 */
const char* npicker(const char* style, const char* title, const char** options, int num_options);

/**
 * @brief asks the user for input with styled text
 * this function displays a prompt and waits for user input
 *
 * @param style the style to use for the prompt ("info", "error", "warn", etc)
 * @param prompt the text to show as the prompt
 * @param buffer a pointer to a character array to store what the user types
 * @param buffer_size the maximum size of the buffer
 *
 * @example
 * char user_input[100];
 * ninput("info", "enter your name", user_input, sizeof(user_input));
 * nprint("success", "hello, [bold]%s[/bold]!", user_input);
 */
void ninput(const char* style, const char* prompt, char* buffer, size_t buffer_size);

#endif // OWIEUTIL_H

// implementation of the functions
#ifdef OWIEUTIL_STYLING

// applies the style to the text by setting up color codes
static void apply_style(const char* style, const char** prefix, const char** dot_color, const char** text_color, const char** bright_color) {
    *prefix = "• ";
    *dot_color = ANSIC_WHITE;
    *text_color = ANSIC_WHITE;
    *bright_color = ANSIC_WHITE;

    // set colors based on style by comparing the style string
    if (strcmp(style, "info") == 0) {
        *prefix = "";
        *text_color = ANSIC_GRAY;
        *bright_color = ANSIC_WHITE;
    } else if (strcmp(style, "error") == 0 || strcmp(style, "err") == 0 || strcmp(style, "red") == 0) {
        *dot_color = ANSIC_RED_DOT;
        *text_color = ANSIC_RED;
        *bright_color = ANSIC_RED_BRIGHT;
    } else if (strcmp(style, "warn") == 0 || strcmp(style, "warning") == 0 || strcmp(style, "orange") == 0 || strcmp(style, "gold") == 0) {
        *dot_color = ANSIC_GOLD_DOT;
        *text_color = ANSIC_GOLD;
        *bright_color = ANSIC_GOLD_BRIGHT;
    } else if (strcmp(style, "success") == 0 || strcmp(style, "green") == 0) {
        *dot_color = ANSIC_GREEN_DOT;
        *text_color = ANSIC_GREEN;
        *bright_color = ANSIC_GREEN_BRIGHT;
    } else if (strcmp(style, "purple") == 0) {
        *dot_color = ANSIC_PURPLE_DOT;
        *text_color = ANSIC_PURPLE;
        *bright_color = ANSIC_PURPLE_BRIGHT;
    } else if (strcmp(style, "blue") == 0) {
        *dot_color = ANSIC_BLUE_DOT;
        *text_color = ANSIC_BLUE;
        *bright_color = ANSIC_BLUE_BRIGHT;
    }
}

// formats the text by adding color codes
static char* format_text(const char* text, const char* text_color, const char* bright_color) {
    char* formatted_text = NULL;
    const char* read_pos = NULL;
    char* write_pos = NULL;

    // alocate memory for formatted text (twice the size to account for color codes)
    formatted_text = malloc(strlen(text) * 2 + 1);
    if (!formatted_text) return NULL;  // return null if memory allocation fails

    // pointers for reading from original text and writing to formatted text
    read_pos = text;
    write_pos = formatted_text;

    // loop through the text and add color codes
    while (*read_pos) {
        if (strncmp(read_pos, "[bold]", 6) == 0) {
            // add bright color code when [bold] is found
            strcpy(write_pos, bright_color);
            write_pos += strlen(bright_color);
            read_pos += 6;
        } else if (strncmp(read_pos, "[/bold]", 7) == 0) {
            // switch back to normal text color when [/bold] is found
            strcpy(write_pos, text_color);
            write_pos += strlen(text_color);
            read_pos += 7;
        } else {
            // copy regular characters as-is
            *write_pos++ = *read_pos++;
        }
    }
    *write_pos = '\0';  // null-terminate the formatted string

    return formatted_text;
}

// prints formatted text with styling and options
void nprint_full(const char* style, const char* text, bool clock, const char* end, FILE* file, ...) {
    const char *prefix = NULL, *dot_color = NULL, *text_color = NULL, *bright_color = NULL;
    va_list args;
    char formatted_with_vars[1024] = {0};  // adjust size if needed
    char* formatted_text = NULL;
    time_t now = 0;
    struct tm *timeinfo = NULL;
    char timestring[9] = {0};

    // check if text is null to avoid crashes
    if (!text) {
        fprintf(stderr, "error: text argument is NULL\n");
        return;
    }
    
    // set default values if not provided
    style = (!style || !*style) ? "info" : style;
    end = end ? end : "\n";
    file = file ? file : stdout;

    // apply the style to get color codes
    apply_style(style, &prefix, &dot_color, &text_color, &bright_color);

    // format the text with variable arguments
    va_start(args, file);
    vsnprintf(formatted_with_vars, sizeof(formatted_with_vars), text, args);
    va_end(args);

    // format the text with colors
    formatted_text = format_text(formatted_with_vars, text_color, bright_color);
    if (!formatted_text) return;  // return if formatting failed

#ifdef _WIN32
    // set console to use utf-8 on windows for proper character display
    SetConsoleOutputCP(CP_UTF8);
#endif

    // print the formatted text
    if (!clock) {
        // print without timestamp
        fprintf(file, "%s%s%s%s%s%s", dot_color, prefix, text_color, formatted_text, end, ANSIC_RESET);
    } else {
        // add timestamp if clock is true
        time(&now);
        timeinfo = localtime(&now);
        strftime(timestring, sizeof(timestring), "%H:%M:%S", timeinfo);
        fprintf(file, "%s%s %s%s%s%s%s%s", dot_color, timestring, ANSIC_GRAY, prefix, text_color, formatted_text, end, ANSIC_RESET);
    }
    free(formatted_text);  // free the memory allocated for formatted text
}

// interactive option picker that displays a menu and lets the user choose an option
const char* npicker(const char* style, const char* title, const char** options, int num_options) {
#ifdef _WIN32
    // Get a handle to the console output device
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Structure to store information about the console screen buffer
    CONSOLE_SCREEN_BUFFER_INFO originalCsbi;
    
    // Pointer to a buffer that will store the contents of the console screen
    CHAR_INFO* buffer;
    
    // Structures to define the size and coordinates of the buffer
    COORD bufferSize, bufferCoord;
    
    // Structure to define the region of the console to be read
    SMALL_RECT readRegion;
#endif
    int selected = 0;
    int key;

#ifdef _WIN32
    // Windows UTF-8
    SetConsoleOutputCP(CP_UTF8);
#endif

    const char *prefix, *dot_color, *text_color, *bright_color;
    apply_style(style, &prefix, &dot_color, &text_color, &bright_color);

#ifdef _WIN32
    // Get original console info
    GetConsoleScreenBufferInfo(hConsole, &originalCsbi);

    // Allocate buffer to store console contents
    bufferSize.X = originalCsbi.dwSize.X;
    bufferSize.Y = originalCsbi.dwSize.Y;
    buffer = malloc(bufferSize.X * bufferSize.Y * sizeof(CHAR_INFO));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Define region to read
    bufferCoord.X = 0;
    bufferCoord.Y = 0;
    readRegion.Left = 0;
    readRegion.Top = 0;
    readRegion.Right = originalCsbi.dwSize.X - 1;
    readRegion.Bottom = originalCsbi.dwSize.Y - 1;

    // Read console contents
    ReadConsoleOutput(hConsole, buffer, bufferSize, bufferCoord, &readRegion);

    // Clear console
    system("cls");
#else
    printf("\033[H\033[J"); // Clear console for Linux
#endif

    while (1) {
        // Print title
        char* formatted_title = format_text(title, text_color, bright_color);
        printf("%s%s:\n\n", bright_color, formatted_title);
        free(formatted_title);

        // Print options
        for (int i = 0; i < num_options; i++) {
            if (i == selected) {
                printf("%s  » %s%s\n", dot_color, text_color, options[i]);
            } else {
                printf("%s    %s\n", text_color, options[i]);
            }
        }

        // Reset color
        printf(ANSIC_RESET);

        // Get user input
        key = getch();

        // Process user input
        switch (key) {
            case 72: // Up arrow (Windows)
            case 'w': // Up arrow (Linux)
                selected = (selected - 1 + num_options) % num_options;
                break;
            case 80: // Down arrow (Windows)
            case 's': // Down arrow (Linux)
                selected = (selected + 1) % num_options;
                break;
            case 13: // Enter (Windows)
            case '\n': // Enter (Linux)
#ifdef _WIN32
                // Clear console
                system("cls");

                // Restore original cursor position
                SetConsoleCursorPosition(hConsole, originalCsbi.dwCursorPosition);

                // Restore original console contents
                WriteConsoleOutput(hConsole, buffer, bufferSize, bufferCoord, &readRegion);

                // Free buffer
                free(buffer);
#else
                printf("\033[H\033[J"); // Clear console for Linux
#endif
                return options[selected];
        }

#ifdef _WIN32
        // Clear console for next iteration
        system("cls");
#else
        printf("\033[H\033[J"); // Clear console for Linux
#endif
    }
}

void ninput(const char* style, const char* prompt, char* buffer, size_t buffer_size) {
    if (!prompt || !buffer) {
        fprintf(stderr, "Error: prompt or buffer is NULL\n");
        return;
    }

    style = (!style || !*style) ? "info" : style;

    const char *prefix, *dot_color, *text_color, *bright_color;
    apply_style(style, &prefix, &dot_color, &text_color, &bright_color);

    char* formatted_prompt = format_text(prompt, text_color, bright_color);
    if (!formatted_prompt) return;

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // Set the console output code page to UTF-8
#endif

    printf("%s? %s%s%s: ", dot_color, text_color, formatted_prompt, bright_color);
    free(formatted_prompt);

    if (fgets(buffer, buffer_size, stdin) != NULL) {
        // Remove trailing newline if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
    }

    printf(ANSIC_RESET);
}


#endif // OWIEUTIL_STYLING

