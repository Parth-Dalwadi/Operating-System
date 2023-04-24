#include "console.h"
#include "keyboard.h"
#include "string.h"
char* const VGA_BUFFER = (char*) 0xb8000;
char int_buffer[11];
char font_color = 0x07;
int term_pos = 0;
char terminal_command[64];
char terminal_options[128];
int space = 0;
	
void clear_terminal(){
	for (int i=0; i < VGA_TOTAL_BYTES; i+=2){
		VGA_BUFFER[i] = 0;
		VGA_BUFFER[i+1] = 0x07;	
	}
	term_pos = 0;
}

void print_character(char c){
	VGA_BUFFER[term_pos++] = c;
	VGA_BUFFER[term_pos++] = font_color;
}

void print_string(char* str){
	for (int i=0; str[i] != '\0'; i++){
		print_character(str[i]);
	}
}

void print_line(char* str){
	print_string(str);
	term_pos = VGA_BYTES_PER_ROW - (term_pos % VGA_BYTES_PER_ROW) + term_pos;	
}

void print_integer(int toPrint){
	itoa(int_buffer, toPrint);
	print_string(int_buffer);
}

void itoa(char* buffer, int toPrint){
	int count = 0;
	int copy = toPrint;

	if (toPrint != 0) {
		while (toPrint != 0){
			toPrint/=10;
			count++;
		}
	} else {
		count = 1;
	}

	for (int i = 0; i < count; i++){
		int num = (copy%10);
		switch(num){
			case 0:
				buffer[i] = 0x30;
				break;
			case 1:
				buffer[i] = 0x31;
				break;
			case 2:
				buffer[i] = 0x32;
				break;
			case 3:
				buffer[i] = 0x33;
				break;
			case 4:
				buffer[i] = 0x34;
				break;
			case 5:
				buffer[i] = 0x35;
				break;
			case 6:
				buffer[i] = 0x36;
				break;
			case 7:
				buffer[i] = 0x37;
				break;
			case 8:
				buffer[i] = 0x38;
				break;
			case 9:
				buffer[i] = 0x39;
				break;
		}	
		copy = copy/10;
	
		
		if (i+1 == count){
			buffer[i+1] = '\0';
		}
	}

	for(int i = count-1; i > 0; i--){
		if (count-1-i >= i) {
			break;
		}
		char temp = buffer[count-1-i];
		buffer[count-1-i] = buffer[i];
		buffer[i] = temp;
	}
	
}

void update_cursor(){
	uint16_t cursor_position = term_pos >> 1;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (cursor_position));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) (cursor_position >> 8));
}

uint16_t get_cursor_position(){
	uint16_t cursor_position = 0;
	outb(0x3D4, 0x0F);
	cursor_position |= inb(0x3D5);
	outb(0x3D4, 0x0E);
	cursor_position |= ((uint16_t)inb(0x3D5)) << 8;
	return cursor_position;
}

int read(unsigned int byte){
	while (byte = scan()) {
		if (charmap[byte] == '\n'){
			if (space == 0){
				terminal_command[get_cursor_position() % VGA_WIDTH - 2] = '\0';
			} else {
				terminal_options[(get_cursor_position() - strlen(terminal_command)) % VGA_WIDTH - 3] = '\0';
			}
			
			int exit = handle_command(terminal_command, terminal_options, 0);

			if (exit == 1){
				return 1;
			}

			print_line("");
			print_string("->");
			space = 0;
		} else {
			print_character(charmap[byte]);
			if (charmap[byte] == ' '){
				space = 1;
				terminal_command[get_cursor_position() % VGA_WIDTH - 2] = '\0';
			} else {

				if (space == 0){
					if (strlen(terminal_command) >= 64 && terminal_command[63] != '\0') {
						terminal_command[63] = '\0';
						handle_command(terminal_command, terminal_options, 1);
					} else {
						terminal_command[get_cursor_position() % VGA_WIDTH - 2] = charmap[byte];
					}	
				} else {
					if (strlen(terminal_options) >= 128 && terminal_options[127] != '\0') {
						terminal_options[127] = '\0';
						handle_command(terminal_command, terminal_options, 2);
					} else {
						terminal_options[(get_cursor_position() - strlen(terminal_command)) % VGA_WIDTH - 3] = charmap[byte];
					}
				}
			}

		}
		update_cursor();
	}
	return 0;
}

int handle_command(char terminal_command[64], char terminal_options[128], int error){
	if (error == 1){
		print_line("");
		print_line("Error: Max command length is 64 characters.");
		print_string("->");
	}

	if (error == 2){
		print_line("");
		print_line("Error: Max length for command and options is 192 characters.");
		print_string("->");
	}

	if (strcmp(terminal_command, "exit") == 0){
		print_line("");
		print_line("Exit: 1");
		update_cursor();
		return 1;
	}	

	if (strcmp(terminal_command, "set-terminal-font-color") == 0){
		if (strcmp(terminal_options, "-black") == 0) {
			font_color = 0x00;
		}else if (strcmp(terminal_options, "-blue") == 0){
			font_color = 0x01;
		}else if (strcmp(terminal_options, "-green") == 0){
			font_color = 0x02;
		} else if (strcmp(terminal_options, "-cyan") == 0){
			font_color = 0x03;
		} else if (strcmp(terminal_options, "-red") == 0){
			font_color = 0x04;
		} else if (strcmp(terminal_options, "-magenta") == 0){
			font_color = 0x05;
		} else if (strcmp(terminal_options, "-brown") == 0){
			font_color = 0x06;
		} else if (strcmp(terminal_options, "-lightgray") == 0){
			font_color = 0x07;
		} else if (strcmp(terminal_options, "-darkgray") == 0){
			font_color = 0x08;
		} else if (strcmp(terminal_options, "-lightblue") == 0){
			font_color = 0x09;
		} else if (strcmp(terminal_options, "-lightgreen") == 0){
			font_color = 0x0a;
		} else if (strcmp(terminal_options, "-lightcyan") == 0){
			font_color = 0x0b;
		} else if (strcmp(terminal_options, "-lightred") == 0){
			font_color = 0x0c;
		} else if (strcmp(terminal_options, "-lightmagenta") == 0){
			font_color = 0x0d;
		} else if (strcmp(terminal_options, "-yellow") == 0){
			font_color = 0x0e;
		} else if (strcmp(terminal_options, "-white") == 0){
			font_color = 0x0f;
		} else {
			print_line("");
			print_string("Invalid color");
		}
	}	
	return 0;
}
