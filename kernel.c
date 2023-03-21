#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_BYTES_PER_CHAR 2
#define TOTAL_BYTES (VGA_WIDTH * VGA_HEIGHT * VGA_BYTES_PER_CHAR)
void main(void){
	char* const VGA_BUFFER = (char*) 0xb8000;
	int term_pos = 0;
	
	void clear_screen(){
		for (int i=0; i < TOTAL_BYTES; i+=2){
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
		term_pos = 160 - (term_pos % 160) + term_pos;	
	}



	clear_screen();
	print_character('H');
	print_character('e');
	char* str = "llo World";
	print_line(str);
	char* str1 = "Today";
	print_string(str1);

	return;
}

