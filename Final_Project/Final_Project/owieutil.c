#include "owieutil.h"

// implementation of the functions

// applies the style to the text by setting up color codes
static void apply_style(const char* style, const char** prefix, const char** dot_color, const char** text_color, const char** bright_color) {
    *prefix = "� ";
    *dot_color = ANSIC_WHITE;
    *text_color = ANSIC_WHITE;
    *bright_color = ANSIC_WHITE;

    // set colors based on style by comparing the style string
    if (strcmp(style, "info") == 0) {
        *prefix = "";
        *text_color = ANSIC_GRAY;
        *bright_color = ANSIC_WHITE;
    }
    else if (strcmp(style, "error") == 0 || strcmp(style, "err") == 0 || strcmp(style, "red") == 0) {
        *dot_color = ANSIC_RED_DOT;
        *text_color = ANSIC_RED;
        *bright_color = ANSIC_RED_BRIGHT;
    }
    else if (strcmp(style, "warn") == 0 || strcmp(style, "warning") == 0 || strcmp(style, "orange") == 0 || strcmp(style, "gold") == 0) {
        *dot_color = ANSIC_GOLD_DOT;
        *text_color = ANSIC_GOLD;
        *bright_color = ANSIC_GOLD_BRIGHT;
    }
    else if (strcmp(style, "success") == 0 || strcmp(style, "green") == 0) {
        *dot_color = ANSIC_GREEN_DOT;
        *text_color = ANSIC_GREEN;
        *bright_color = ANSIC_GREEN_BRIGHT;
    }
    else if (strcmp(style, "purple") == 0) {
        *dot_color = ANSIC_PURPLE_DOT;
        *text_color = ANSIC_PURPLE;
        *bright_color = ANSIC_PURPLE_BRIGHT;
    }
    else if (strcmp(style, "blue") == 0) {
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

    // allocate memory for formatted text (twice the size to account for color codes)
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
        }
        else if (strncmp(read_pos, "[/bold]", 7) == 0) {
            // switch back to normal text color when [/bold] is found
            strcpy(write_pos, text_color);
            write_pos += strlen(text_color);
            read_pos += 7;
        }
        else {
            // copy regular characters as-is
            *write_pos++ = *read_pos++;
        }
    }
    *write_pos = '\0';  // null-terminate the formatted string

    return formatted_text;
}

// prints formatted text with styling and options
void nprint_full(const char* style, const char* text, bool clock, const char* end, FILE* file, ...) {
    const char* prefix = NULL, * dot_color = NULL, * text_color = NULL, * bright_color = NULL;
    va_list args;
    char formatted_with_vars[1024] = { 0 };  // adjust size if needed
    char* formatted_text = NULL;
    time_t now = 0;
    struct tm* timeinfo = NULL;
    char timestring[9] = { 0 };

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
    }
    else {
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

    const char* prefix, * dot_color, * text_color, * bright_color;
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
            }
            else {
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


            // Return the selected option
            return options[selected];
#else
            // Clear console for Linux
            printf("\033[H\033[J");

            // Return the selected option
            return options[selected];
#endif
        default:
            // Ignore other keys
            break;
        }

#ifdef _WIN32
        // Clear console and set original screen buffer
        WriteConsoleOutput(hConsole, buffer, bufferSize, bufferCoord, &readRegion);
#else
        // Clear console for Linux
        printf("\033[H\033[J");
#endif
    }

#ifdef _WIN32
    // Free allocated buffer memory
    free(buffer);
#endif

    // Default return
    return NULL;
}

void ninput(const char* style, const char* prompt, char* buffer, size_t buffer_size) {
    if (!prompt || !buffer) {
        fprintf(stderr, "Error: prompt or buffer is NULL\n");
        return;
    }

    style = (!style || !*style) ? "info" : style;

    const char* prefix, * dot_color, * text_color, * bright_color;
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
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }

    printf(ANSIC_RESET);
}