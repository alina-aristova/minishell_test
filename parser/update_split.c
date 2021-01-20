
#include <stdlib.h>
#include<stdio.h>
static char		*ft_make_new_substr(char const *start, char const *end)
{
	char *substr;
	char *tmp;
	int i = 0;
	int flg = 0;
	// while (start[i] != end[i])
	// {
	// 	if(*start == '\'')
	// 		i++;
	// 	if(*start == '\"')
	// 		i++;
	// 	i++;
	// // }
	// printf("start---> %s\n",start);
	// printf("*end---> %s\n",end);
	substr = (char *)malloc((i) + 2);
	tmp = substr;
	
	while (start != end)
	{
		// if(*start == '\'' && flg == 1)
		// 	start++;
		// if(*start == '\"'&& flg == 2)
		// 	start++;
		// if (flg == 0)
		// {
		// 	if(*start == '\'')
		// 	{
		// 		start++;
		// 		flg = 1;
		// 	}
		// 	if(*start == '\"')
		// 	{
		// 		start++;
		// 		flg = 2;
		// 	}
		// }
		*substr = *start;
		substr++;
		start++;
	}
	*substr = '\0';
	return (tmp);
}
char *skip_line(char *s,char c)
{
	if (*s == c)
		s++;
	while(*s != c && *s != '\0')
	{
		if(*s == '\'')
		{
			s++;
			while(*s != '\'')
				s++;
			//if(*(s+1) != '\0')	
			//	s++;
		}
		if(*s == '\"')
		{
			s++;
			while(*s != '\"')
				s++;
			//if(*(s+1) != '\0')	
				//s++;
		}
		s++;
	}
	return(s);
}
static int	ft_count_strs(char const *s1, char c)
{
	int count;

	count = 0;
	char *s = (char*)s1;
	while (*s != '\0')
	{
		if(*s != c || *s != '\0')
			s = skip_line(s,c);
		count++;
		s++;
	}
	return (count);
}

static char		**ft_clean_if_fail(char **s, size_t last_word)
{
	while (last_word > 0)
	{
		free(s[last_word--]);
	}
	free(s[0]);
	free(s);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char			**res;
	const char		*tmp;
	size_t			word_counter;
	size_t			current_word;
	int i = 0;

	if (s == NULL)
		return (NULL);
	word_counter = ft_count_strs(s, c);
	if(!(res = (char **)malloc((word_counter + 1) * sizeof(char *))))
		return (NULL);
	current_word = 0;
	while (current_word < word_counter)
	{
		while (s[i] && s[i] == c)
		 	i++;
		tmp = &s[i];
		while(s[i] != c && s[i] != '\0')
		{
			if(s[i] == '\'')
			{
				tmp++;
				i++;
				while(s[i] != '\'')
					i++;
				//i++;
			}
			if(s[i] == '\"')
			{
				tmp++;
				i++;
				while(s[i] != '\"')
					i++;
				//i++;
			}
			i++;
		}
		
		
		res[current_word] = ft_make_new_substr(tmp, &s[i]);
		if (res[current_word++] == NULL)
			return (ft_clean_if_fail(res, current_word - 1));
	}
	res[current_word] = NULL;
	return (res);
}
#include<stdio.h>
int main()
{
	int r = ft_count_strs("\'123\";\";456\'\\;\';\'789",';');
	printf("%d\n",r);
	char **s;
	int i = 0;
	s = ft_split("\'123\';456;789 ",';');
	while(s[i])
	{
		printf("|%s|\n",s[i]);
		i++;
	}
}