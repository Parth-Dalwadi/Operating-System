#include "console.h"
#include "keyboard.h"
void main(){
	clear_terminal();
	//print_character('H');
	//print_character('e');
	//print_line("llo World");
	//print_string("TODAY");
	print_integer(131567);
	print_integer(2789);
	unsigned char byte;
	while (1) {
		while (byte = scan()) {
			print_character(charmap[byte]);
			update_cursor();
		}
	}
	//print_character_with_color("A", BLACK, YELLOW);
	//print_character_with_color("A", 0x00, 0x0E);

	return;
}

