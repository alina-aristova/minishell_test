
#include <stdlib.h>
#include<stdio.h>
static char		*ft_make_new_substr(char const *start, char const *end)
{
	char *substr;
	char *tmp;
	int i = 0;
	int flg = 0;

	substr = (char *)malloc((end - start) + 2);
	tmp = substr;
	
	while (start != end)
	{
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
			while(*s != '\''&&*s != '\0')
				s++;
		}
		if(*s == '\"')
		{
			s++;
			while(*s != '\"' &&*s != '\0' )
				s++;
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
		if(*s != '\0')
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

char			**update_split(char const *s, char c)
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
				i++;
				while(s[i] != '\'')
					i++;
			}
			if(s[i] == '\"')
			{
				i++;
				while(s[i] != '\"')
					i++;
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

// #include<stdio.h>
// int main()
// {
// 	char **s;
// 	int i = 0;
// 	s = update_split("'e''c'ho a > qw|echo b>qwerty|'c'a't' -e ; 'e''c'ho a > qw| echo b>qwerty | 'c'a't' -e                ",';');
// 	while(s[i])
// 	{
// 		printf("|%s|\n",s[i]);
// 		i++;
// 	}
// }