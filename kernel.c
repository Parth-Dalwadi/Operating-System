#include "console.h"
#include "keyboard.h"
//char terminal_command[64];
//char terminal_options[128];
//int count = 0;
//int space = 0;

void main(){
	clear_terminal();
	print_string("->");
	update_cursor();
	unsigned char byte;
	while (1) {
		//if (read(byte) == 1){
		//	print_integer(2);
		//	break;
		//} else{
		//	read(byte);
		//}
		int exit = read(byte);
		if (exit == 1){
			break;
		}
	}

	return;
}

