#ifndef H_CONSOLE
#define H_CONSOLE
#include <stdint.h>
#include <stddef.h>
void clear_terminal();
void print_character(char c);
void print_string(char* str);
void print_line(char* str);
void update_cursor();
uint16_t get_cursor_position();
void print_integer(int toPrint);
void itoa(char* buffer, int toPrint);
int read(unsigned int byte);
int handle_command(char terminal_command[64], char terminal_options[128], int error);
void shift_terminal_up();
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_BYTES_PER_CHARACTER 2
#define VGA_BYTES_PER_ROW (VGA_WIDTH*VGA_BYTES_PER_CHARACTER)
#define VGA_TOTAL_BYTES (VGA_WIDTH*VGA_HEIGHT*VGA_BYTES_PER_CHARACTER)
#endif
