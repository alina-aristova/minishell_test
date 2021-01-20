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

int main()
{
	char *str;
	int start = 0;
	int finish = 0;
	char **str1;
	str1 = (char**)malloc(sizeof(char**)*20);
		int i = 0;
	str = "ls -la -ls | cat>  ~;  d<    a      > dfg";
	while(str[start])
	{
		
		//printf("str[finish] --> |%c|\n",str[finish]);
		if((str[finish] == ' ' || str[finish] == '>' || str[finish] == '<' || str[finish] == '\0'))
		{
			
			//printf("str[finish] --> |%c|\n",str[finish]);
			//printf("|%d|<--->|%d|",start,finish);
			str1[i] = ft_substr(str,start,finish - start);
			i++;
			
			while(str[finish] == ' ' || str[finish] == '>' || str[finish] == '<')
			{
				if((str[finish] == '>' || str[finish] == '<'))
				{
					str1[i] = str[finish] == '>' ? ft_strdup(">") : ft_strdup("<");
					i++;
				}
				finish++;
			}
			start = finish;
			
		}
		
		finish++;
	}
	str1[i] = NULL;
	
	while(*str1)
	{
		printf("|%s|\n",*str1++);
	}
	
}