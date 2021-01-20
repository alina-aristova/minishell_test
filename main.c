#include "libft.h"
#include "minishell.h"

int size_of_2d_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

char **reallocate_envp(char **envp)
{
	char	**env;
	int 	i;

	i = 0;
	env = (char **)malloc((size_of_2d_array(envp) + 1) * sizeof(char *));
	while (envp[i] != NULL)
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

void clear_2d_arrr(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}

void reallocate_string(char **str, int *buffer_size)
{
	char *buf;
	char *to_del;

	buf = calloc(*buffer_size * 2, sizeof(char));
	if (buf == NULL)
		exit_malloc();
	ft_strlcpy(buf, *str, *buffer_size);
	*buffer_size *= 2;
	to_del = *str;
	*str = buf;
	free(to_del);
}

int gnl_shell(char **line)
{
	int buffer_size;
	char c;
	int flag;
	int pos;
	int pipe;

	buffer_size = 512;
	*line = ft_calloc(buffer_size ,sizeof(char));
	pos = 0;
	pipe = 0;
	if (*line == NULL)
		exit_malloc();
	while ((flag = read(0, &c, 1)) > 0 && c != '\n')
	{
		if (pos + 1 >= buffer_size)
			reallocate_string(line, &buffer_size);
		(*line)[pos++] = c;
		if (pipe == 0 && c == '|')
			pipe = 1;
		else if (pipe == 1 && c != ' ')
			pipe = 0;
	}
	if (flag <= 0)
		exit(1);
	return (pipe);
}

void gnl_pipe(char **line, int *pipe)
{
	int buffer_size;
	char c;
	int flag;
	int pos;

	buffer_size = 512;
	*line = ft_calloc(buffer_size ,sizeof(char));
	pos = 0;
	if (*line == NULL)
		exit_malloc();
	while ((flag = read(0, &c, 1)) > 0 && c != '\n')
	{
		if (pos + 1 >= buffer_size)
			reallocate_string(line, &buffer_size);
		(*line)[pos++] = c;
		if (*pipe == 0 && c == '|')
			*pipe = 1;
		else if (*pipe == 1 && c != ' ')
			*pipe = 0;
	}
	if (flag <= 0)
		exit(1);
}

void shell_read(char **line)
{
	int pipe;
	char *next_line;
	char *buf;

	pipe = gnl_shell(line);
	while (pipe == 1)
	{
		ft_putchar_fd('>', 1);
		ft_putchar_fd(' ', 1);
		gnl_pipe(&next_line, &pipe);
		buf = ft_strjoin(*line, next_line);
		free(*line);
		free(next_line);
		*line = buf;
	}
}

int main(int argc, char **argv, char **envp)
{
	int i;
	char *line;


	while (1)
	{
		ft_putstr_fd("minishell> ", 0);
		shell_read(&line);
		printf("%s\n", line);
		//Дальше в парсер line, получаем из него структуру, запускаем выполнение
		free(line);
	}
	return 0;
}
