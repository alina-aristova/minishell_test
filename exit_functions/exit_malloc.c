
#include "exit.h"

void exit_malloc()
{
	strerror(errno);
	exit(1);
}