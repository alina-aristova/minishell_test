#include <stdlib.h>
#include <stdio.h>
#include "../includes/pars.h"
#include <unistd.h>
#include <stdio.h>
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
		{	count++;
			//printf("%d,,,%s\n",count,str[i]);
			//printf("%d\n",str[i]);
			}
		i++;
	}
	j= 0;
	i = 0;
	char **stres = malloc((count + 1)*(sizeof(char*)));
	while(str[i])
	{
		if(ft_strlen(str[i])!= 0)
		{	stres[j] = str[i];
			j++;
			//printf("%d,,,%s\n",count,str[i]);
			//printf("%d\n",str[i]);
			}
		i++;
	}
	stres[j] = NULL;
	return(stres);
}
void fill_struct(t_shell *shell, char *str, int len)
{
	char **str_args;
	int i = 0;

	str_args = cat_string(str);
	str_args = refactor_str(str_args);
	shell[len].argv = malloc(100);
	while(str_args[i])
	{
		//
		//printf("%s\n",str_args[i]);
		//printf("%s\n",str_args[i-1]);
		// if(empty_line(str_args[i]))
		// 	i++;
	//	if(!empty_line(str_ar=gs[i]))
		//{
			if (i == 0)
			{
				//printf("%d\n",i);
				if((!is_redirectoin(str_args[i])))
				{
				//	printf("%s\n",str_args[i]);
					shell[len].argv[i] = str_args[i];
				}
			}
			else if((!is_redirectoin(str_args[i]) && !is_redirectoin(str_args[i - 1])))
			{
				//printf("%s\n",str_args[i]);
				shell[len].argv[i] = str_args[i];
				//i++;
			}
			//printf("%s\n",str_args[i]);
			
			
	//	}
		i++;
	}
		shell[len].argv[i] = NULL;
		i = 0;
		
	
}
void init_shell_structs(t_shell *shell, int size)
{
	int i = 0;
	while(i < size)
	{
		shell[i].argv = NULL;
		shell[i].input = 1;
		shell[i].output = 0;

		
		i++;	
	}
}
int red_between_pipes(t_shell *shell, int len)
{
	int i = 0;
	int pipes[2];
	while(i < len - 1)
	{
		if (pipe(pipes) < 0)
			return (-1);
		shell[i + 1].input = pipes[0];
		shell[i].output= pipes[1];
		i++;
	}
	return(0);

}
t_all *get_args(t_all *all, char *str)
{
	char **str_pipe;
	int size_arr;
	int i ;

	i = 0;
	str_pipe = update_split(str,'|');
	size_arr = size_of_2d_array(str_pipe);
	all->shell = malloc((size_arr) * sizeof(t_shell));
	//all->shell[size_arr] = NULL;
	init_shell_structs(all->shell,size_arr);

	red_between_pipes(all->shell, size_arr);
	while(i < size_arr)
	{
		fill_struct(&(all->shell[i]),str_pipe[i], i);
		i++;

	}
	i = 0;
	
	return(all);
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

	while(s[i])
	{
		all = *get_args(&all, s[i]);
		
		//вызываем команды
		i++;
	}
	i = 0;
	while(i < 3)
	{
		j = 0;
		while(all.shell[i].argv[j])
		{
			fprintf(stderr, "|shell[i]: %d|argv[j]: %d|input: %d|output: %d|arg: %s|\n",i,j,all.shell[i].input, all.shell[i].output,all.shell[i].argv[j]);
			j++;
		}
		i++;
	}
}