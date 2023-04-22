#include "console.h"
#include "keyboard.h"

void main(){
	clear_terminal();
	print_string("->");
	update_cursor();
	unsigned char byte;
	while (1) {
		int exit = read(byte);
		if (exit == 1){
			break;
		}
	}

	return;
}

