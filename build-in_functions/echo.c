#include "libft.h"

int echo(int argc, char **argv)
{
	int i;
	int flag;

	flag = ft_strncmp(argv[0], "-n", 10);
	i = flag != 0? 0: 1;
	while (ft_strncmp(argv[i], "-n", 10))
	{
		i++;
	}
	while (i < argc)
	{
		ft_putstr_fd(argv[i++], 1);
	}
	if (flag != 0)
		ft_putchar_fd('\n', 1);
	return (0);
}