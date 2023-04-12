#include "console.h"
#include "keyboard.h"
void main(){
	clear_terminal();
	update_cursor();
	unsigned char byte;
	while (1) {
		while (byte = scan()) {
			print_character(charmap[byte]);
			print_integer(get_cursor_position());
			update_cursor();
		}
	}

	return;
}

