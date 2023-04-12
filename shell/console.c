#include "console.h"
char* const VGA_BUFFER = (char*) 0xb8000;
char int_buffer[11];
int term_pos = 0;
	
void clear_terminal(){
	for (int i=0; i < VGA_TOTAL_BYTES; i+=2){
		VGA_BUFFER[i] = 0;
		VGA_BUFFER[i+1] = 0x07;	
	}
	term_pos = 0;
}

void print_character(char c){
	VGA_BUFFER[term_pos++] = c;
	VGA_BUFFER[term_pos++] = 0x07;
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
