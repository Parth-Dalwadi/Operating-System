#include "console.h"
char* const VGA_BUFFER = (char*) 0xb8000;
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
