#include "signals.h"


void signal_handler(int signum)
{
	char msg[] = "Gotcha! [0]\n";

	msg[9] = signum + '0';
	write(1, msg, 12);
}


int handle_signal(void)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR)
		return (-1);
	return (0);
}
