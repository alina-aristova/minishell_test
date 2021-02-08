#include <stdlib.h>
#include <stdio.h>
#include "../includes/pars.h"
#include <unistd.h>
#include <stdio.h>
# include <fcntl.h>
void clear_2d_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
}
int size_of_2d_array(char **arr)
{
	int i;

	i = 0;
	if(!arr)
		return(0);
	while (arr[i] != NULL)
		i++;
	return (i);
}
char    *arrstrs_addback(char ***arr, char *s)
{
	char	**res;
	size_t	len;

	if (arr == NULL || s == NULL)
		return (NULL);
	len = size_of_2d_array(*arr) + 1;
	if ((res = (char**)malloc(sizeof(char*) * (len + 1))) == NULL)
	{
		clear_2d_arr(*arr);
		return (NULL);
	}
	res[len--] = NULL;
	res[len] = s;
	while (len-- != 0)
	{
		res[len] = (*arr)[len];
	}
	free(*arr);
	*arr = res;
	return(s);
}
int is_separator(char c)
{
	if(c == ' ' || c == ';' || c == '>' || c == '<' || c == '|' )
		return(1);
	return(0);
}
int is_q(char c)
{
	if(c == '\'')
		return(1);
	return(0);
}

int check_len_sub(char *str)
{
	int flg_q;
	flg_q = 0;
	int res_len;
	res_len = 0;

	while(*str)
	{
		if(*str == '\'')
		{
			str++;
			while(*str != '\'' && *str != '\0')
			{
				str++;
				res_len++;
			}
			str++;
		}
		else
		{
			str++;
			res_len++;
		}
	}
	return(res_len);
}
char			*shell_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	char	*tmp;
	//printf("|%s|\n",s);
	if (s == NULL)
		return (NULL);
	if ((size_t)start > (size_t)ft_strlen(s))
		return (ft_strdup(""));
	int res_len = check_len_sub((char*)s); 
	if (!(res = (char *)malloc((res_len + 1) * sizeof(char))))
		return (NULL);
	tmp = res;
	s += start;
	while (*s && len != 0)
	{
		while(*s==' ')
		{
			s++;
			len--;
		}
		if(*s == '\'')
		{
			s++;
			len--;
			while(*s != '\'' && *s != '\0')
			{
				*tmp = *s;
				tmp++;
				s++;
				len--;
			}
			len--;
			s++;
		}
		else
		{
			*tmp = *s;
			tmp++;
			s++;
			len--;
		}
		
	}
	*tmp = '\0';
	return (res);
}
int shell_count_strs(char *str)
{
	int start = 0;
	int finish = 0;
	int i = 0;
	while(str[start])
	{
		if(is_q(str[finish]))
		{
			finish++;
			while(!is_q(str[finish]))
				finish++;
			if(is_separator(str[finish + 1]))
			{
				i++;
				finish++;
				start = finish;
			}
			finish++;
		}
		else if(is_separator(str[finish]) || str[finish] == '\0' )
		{
			i++;
			while(is_separator(str[finish]))
			{
				if((str[finish] == '>' || str[finish] == '<'))
					i++;
				if((str[finish] == '|' || str[finish] == ';'))
					i++;
				finish++;
			}
			start = finish;
		}
		else
			finish++;
		}
	return(i);
}
char **cat_string(char *str)
{
	//char *str;
	int start = 0;
	int finish = 0;
	char **str1;
	
	int i = 0;
	//int res = check_len_sub("hello\'world\'he\'llo\'");
	//str = "\'e\'\'c\'ho a | echo b > qwerty | 'c'a't' -e";
	int count = shell_count_strs(str);
	str1 = (char**)malloc(sizeof(char**)*(count + 1));
	while(str[start])
	{
		if(is_q(str[finish]))
		{
			finish++;
			while(!is_q(str[finish]))
				finish++;
			if(is_separator(str[finish+1]))
			{
				str1[i] = shell_substr(str,start,finish - start + 1);
				i++;
				finish++;
				start = finish;
			}
			finish++;
		}
		else if(is_separator(str[finish]) || str[finish] == '\0' )
		{
			str1[i] = shell_substr(str,start ,finish - start );
			i++;
			
			while(is_separator(str[finish]))
			{
				if((str[finish] == '>' || str[finish] == '<'))
				{
					str1[i] = str[finish] == '>' ? ft_strdup(">") : ft_strdup("<");
					i++;
				}
				if((str[finish] == '|' || str[finish] == ';'))
				{
					str1[i] = str[finish] == '|' ? ft_strdup("|") : ft_strdup(";");
					i++;
				}
				finish++;
			}
			start = finish;
		}
		else
			finish++;
	}
	str1[i] = NULL;
	return(str1);
	
}

int empty_line(char *str)
{
	if(!str)
		return(TRUE);
	if(ft_strlen(str) == 0)
		return(TRUE);
	return(FALSE);
}

void count_semicolon(t_all *all, char **str)
{
	all->flgs.count_sem = size_of_2d_array(str);
}
int is_redirectoin(char * str)
{
	if(!ft_memcmp(str,">",2) || !ft_memcmp(str,"<",2) 
	|| !ft_memcmp(str,">>",3))
		return(TRUE);
	return(FALSE);
}
char **refactor_str(char **str)
{
	int count;
	int i = 0;
	count = 0;
	int j;
	while(str[i])
	{
		if(ft_strlen(str[i])!= 0)
			count++;	
		i++;
	}
	j= 0;
	i = 0;
	char **stres = malloc((count + 1)*(sizeof(char*)));
	while(str[i])
	{
		if(ft_strlen(str[i])!= 0)
		{	stres[j] = ft_strdup(str[i]);
			j++;
		}
		i++;
	}
	stres[j] = NULL;
	//free(str);
	return(stres);
}
int count_red(char **str)
{
	int i = 0;
	while(*str)
	{
		if(is_redirectoin(*str))
		{
			i++;
		} 
		str++;
	}
	return(i);
} 
char **fill_struct(t_shell *shell, char *str, int len)
{
	char **str_args;
	char **str_args1;
	int i = 0;
	int count;
	
	str_args1 = cat_string(str);
	str_args = refactor_str(str_args1);
	clear_2d_arr(str_args1);
	count = size_of_2d_array(str_args) - 2 * count_red(str_args);
	printf("count args %d\n",count);
	shell[len].argv = malloc((count + 1)*sizeof(char*));
	while(str_args[i])
	{

			if (i == 0)
			{
				if((!is_redirectoin(str_args[i])))
				{
					shell[len].argv[i] = str_args[i];
					printf("|%s|%d|%d\n",shell[len].argv[i],i,len);
				}
			}
			else if((!is_redirectoin(str_args[i]) && !is_redirectoin(str_args[i - 1])))
			{
				shell[len].argv[i] = str_args[i];
				printf("|%s|%d|%d\n",shell[len].argv[i],i,len);

			}
		i++;
	}
	shell[len].argv[i] = NULL;
		i = 0;
	//clear_2d_arr(str_args1);	
	return(str_args);
}
void init_shell_structs(t_shell *shell, int size)
{
	int i = 0;
	while(i < size)
	{
		shell[i].argv = NULL;
		shell[i].input = 1;
		shell[i].output = 0;
		printf("i: |%d| shell[i].input: |%d| shell[i].output: |%d|\n",i, shell[i].input, shell[i].output);
		i++;	
	}
}
int pipes(t_shell *shell, int len)
{
	int i = 0;
	int pipes[2];
	while(i < len - 1)
	{
		if (pipe(pipes) < 0)
			return (-1);
		shell[i + 1].input = pipes[0];
		shell[i].output = pipes[1];
		printf("pipes[0]:|%d| pipes[1]:|%d|\n",pipes[0],pipes[1]);
		printf("i: |%d| shell[i + 1].input: |%d| shell[i].output: |%d|\n",i, shell[i + 1].input, shell[i].output);
		i++;	
		//i++;
	}
	return(0);
}

int redirection(t_shell *shell, char **str, int len)
{
	int i = 0;
	int fd = 0;
	while(str[i])
	{
		if(!memcmp(str[i],">",2))
		{
			if ((fd =  open(str[i + 1], O_CREAT | O_WRONLY | O_TRUNC,
								0644)) < 0)
								return(ERROR);
			if(shell->output != 0)
				close(shell->output);
			shell->output = fd;
			i++;
			
		}
		if(!memcmp(str[i],">>",3))
		{
			if ((fd =  open(str[i + 1], O_CREAT | O_WRONLY | O_APPEND,
								0644)) < 0)
								return(ERROR);
			if(shell->output != 0)
				close(shell->output);
			shell->output = fd;
			i++;
		}
		if(!memcmp(str[i],"<",2))
		{
			if ((fd =  open(str[i + 1],  O_RDONLY )) < 0)
								return(ERROR);
			if(shell->input != 1)
				close(shell->input);
			shell->output = fd;
			i++;	
		}
		i++;

	}
	return(TRUE);
}
void get_args(t_all *all, char *str)
{
	char **str_pipe;
	int size_arr;
	int i ;
	char **res_fill;
	i = 0;
	str_pipe = update_split(str,'|');
	size_arr = size_of_2d_array(str_pipe);
	all->shell = malloc((size_arr) * sizeof(t_shell));
	init_shell_structs(all->shell, size_arr);
	pipes(all->shell, size_arr);
	while(i < size_arr)
	{
		res_fill = fill_struct(&(all->shell[i]),str_pipe[i], i);
		redirection(&(all->shell[i]),res_fill, i);
		///clear_2d_arr(res_fill);
		i++;
	}
	clear_2d_arr(str_pipe);
}
int main()
{
	t_all all;
	char **s;
	
	int i;
	i = 0;
	int j;
	int k = 0;

	s = update_split(" ls -la 'e''c'ho a > qw|echo b>qwerty|'c'a't' -e ; 'e''c'ho c > qw| echo qwe>qwerty | 'c'a't' -e                ",';');
	count_semicolon(&all, s);

	ft_bzero(&all, sizeof(t_all));
	while(s[i])
	{
		
		get_args(&all, s[i]);
		//вызываем команды
		
		//clear_2d_arr(all.shell->argv);
		//free(all.shell);
		i++;
	}
	i = 0;
	clear_2d_arr(s);
	//sleep(100);

}