#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "dbg.h"

void dbg_glue_init(){
	struct termios ctrl;

	tcgetattr(STDIN_FILENO, &ctrl);
	ctrl.c_lflag &= ~ICANON; // turning off canonical mode makes input unbuffered
	ctrl.c_lflag &= ~ECHO; // turning off local echo
	tcsetattr(STDIN_FILENO, TCSANOW, &ctrl);
}

void dbg_terminal_cyclic(){
	char buffer;

	fcntl(STDIN_FILENO , F_SETFL, fcntl(STDIN_FILENO , F_GETFL) | O_NONBLOCK);
	
	int bytes_read = read(STDIN_FILENO, &buffer, 1);

	if (bytes_read > 0){
		if(buffer == 0x0A)
			buffer = 0x0D;

		dbg_handle_input(buffer);
	}
}
