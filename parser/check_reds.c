/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acase <acase@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:58:53 by acase             #+#    #+#             */
/*   Updated: 2021/01/18 19:05:26 by acase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pars.h"

#include <stdio.h>

static void		skipwhitespace(const char **str)
{
	while (**str == ' ' || **str == '\n' || **str == '\t' || **str == '\v'
	|| **str == '\f' || **str == '\r')
		(*str)++;
}
int check_reds(const char *str)
{
	skipwhitespace(&str);
	if(*str == ';' || *str == '|')
		return(FALSE);
	while(*str)
	{
		if(*str == '\'')
		{
			while(*str != '\'')
				str++;
			//str++;
		}
		if(*str == '\"')
		{
			while(*str != '\"')
				str++;
			//str++;
		}
		if(*str == '>'|| *str == '<')
		{
			if(*str == '>' && *(str + 1) == '>')
				str++;
			str++;
			skipwhitespace(&str);
			if( *str == '\0' || *str == '|'||*str == ';' ||
			 *str == '>' || *str == '<' )
			return(FALSE);
		}
		str++;
	}
	return(TRUE);
}
#include<stdio.h>
int main()
{
	int i = check_reds("a \'>>      >>  ");
	printf("%d\n",i);
}
