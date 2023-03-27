#ifndef H_CONSOLE
#define H_CONSOLE
void clear_terminal();
void print_character(char c);
void print_string(char* str);
void print_line(char* str);
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_BYTES_PER_CHARACTER 2
#define VGA_BYTES_PER_ROW (VGA_WIDTH*VGA_BYTES_PER_CHARACTER)
#define VGA_TOTAL_BYTES (VGA_WIDTH*VGA_HEIGHT*VGA_BYTES_PER_CHARACTER)
#endif
