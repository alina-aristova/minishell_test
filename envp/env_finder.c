#include "libft.h"
#include "minishell.h"

static char	*get_value(char *env, const char *key)
{
	int i;

	i = 0;
	while (env[i] != '\0' && env[i] != '=')
	{
		if (env[i] != key[i])
			return (NULL);
		i++;
	}
	if (env[i] == '=' && key[i] == '\0')
		return (&(env[i + 1]));
	return (NULL);
}

/*
 ** return address of value, need to be freed!!!
*/

char		*env_finder(char *key, char **env)
{
	int		i;
	char	*value;

	i = 0;
	while (env[i] != NULL)
	{
		if ((value = get_value(env[i], key)) != NULL)
		{
			value = ft_strdup(value);
			break ;
		}
		i++;
	}
	return (value);
}
