#include "console.h"
void main(){
	clear_terminal();
	print_character('H');
	print_character('e');
	print_line("llo World");
	print_string("TODAY");
	//print_character_with_color("A", BLACK, YELLOW);
	//print_character_with_color("A", 0x00, 0x0E);

	return;
}

