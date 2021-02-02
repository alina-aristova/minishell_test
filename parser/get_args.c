#include <stdlib.h>
#include <stdio.h>
#include "../includes/pars.h"

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
// void init_params(t_all *all)
// {
// 	all->shell.argv = NULL;

// }
int empty_line(char *str)
{
	if(!str)
		return(FALSE);
	if(ft_strlen(str)== 0)
		return(TRUE);
	return(FALSE);
}

void count_semicolon(t_all *all, char **str)
{
	all->flgs.count_sem = size_of_2d_array(str);
}

void check_count_pipe(t_all *all, char ***str)
{
	int i;
	i = 0;

	all->flgs.count_pipe = (int*)malloc(all->flgs.count_sem * sizeof(int));
	while(str[i])
	{
		all->flgs.count_pipe[i] = size_of_2d_array(str[i]);
		i++;
	}	
}
void get_args(t_all *all, char **str)
{

	int i = 0;
	while(str && *str)
	{

		printf("%s\n",   str[i]);
		i++;
	}
	// {
	// 	if(!empty_line(*str))
	// 	{
	// 			if(!ft_memcmp(*str,">",1))
	// 			{
	// 				(*str)++;
	// 			}
	// 			else if(!ft_memcmp(*str,"<",1))
	// 				(*str)++;
	// 			else if(!ft_memcmp(*str,">>",2))
	// 				(*str)++;
	// 			else
	// 			{
	// 				arrstrs_addback((&(all->shell[0][0].argv)),*str);
	// 				(*str)++;
	// 			}
	// 	}
	// 	else
	// 	(*str)++;	
	// }
	
}
int main()
{
	t_all all;
	char **s;
	
	int i;
	i = 0;
	int j;
	int k = 0;
	//int i = 0;
	s = update_split("'e''c'ho a > qw|echo b>qwerty|'c'a't' -e ; 'e''c'ho a > qw| echo b>qwerty | 'c'a't' -e                ",';');
	//char **str_res = cat_string("\'e\'\'c\'ho a > qw|echo b>qwerty|'c'a't' -e ; \'e\'\'c\'ho a > qw| echo b>qwerty | 'c'a't' -e                ");
	count_semicolon(&all, s);
	//s_pipe = (char***)(malloc(sizeof(char**) * (all.flgs.count_sem + 1) ));
	while(s[i])
	{
		//s_pipe[i] = update_split(s[i],'|');
		i++;
	}
}