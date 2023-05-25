#include "shell_header.h"

/*
 * get_Signal - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void get_Signal(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n $$ ", 5);
}
