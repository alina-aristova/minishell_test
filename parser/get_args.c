#include <stdlib.h>
#include<stdio.h>
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
			if(is_separator(str[finish+1]))
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
int main()
{
	char *str;
	int start = 0;
	int finish = 0;
	char **str1;
	
	int i = 0;
	str = "\'e\'\'c      \'\'h\'\'o\' -la -ls\'|\' cat>\';  d<    a\'\' > \'dfg ";
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
				str1[i] = ft_substr(str,start,finish - start + 1);
				i++;
				finish++;
				start = finish;
			}
			finish++;
			//start = finish;
			//finish++;
		}
		else if(is_separator(str[finish]) || str[finish] == '\0' )
		{
			str1[i] = ft_substr(str,start+1,finish - start -1);
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
			//finish++;
			start = finish;
			//finish++;
		}
		else
			finish++;
		//finish++;
	}
	str1[i] = NULL;
	printf("count--->|%d|\n",count);
	while(*str1)
	{
		printf("|%s|\n",*str1++);
	}
	
}