
#include "build-in_functions.h"
#include <unistd.h>

int pwd()
{
	char *buf;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
		return (-1);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}
