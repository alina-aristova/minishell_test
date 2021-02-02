/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acase <acase@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:51:30 by acase             #+#    #+#             */
/*   Updated: 2021/01/28 13:43:38 by acase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pars.h"
#include<stdio.h>
static void singl_quote(char *str, t_flgs *flg)
{	
	if(flg->flg_one == 0)
	{
		if(flg->flg_two == 0)
			flg->flg_one = 1;
		else
			return;	
	}
	else
		flg->flg_one = 0;	
}		

static void double_quote(char *str, t_flgs *flg)
{
	if(flg->flg_two == 0)
	{
		if(flg->flg_one == 0)
			flg->flg_two = 1;
		else
			return ;
	}
	else
		flg->flg_two = 0;
}

int check_quotes(const char *str1, t_flgs *flg)
{
	flg->flg_two = 0;
	flg->flg_one = 0;
	char *str = (char*)str1;
	while(*str)
	{
		printf("%s\n","i");
		if(!ft_memcmp(str,"\'",1) || !ft_memcmp(str,"\"",1))
				!ft_memcmp(str,"\'",1) ? singl_quote(str,flg) : 
				double_quote(str,flg);
		str++;	
	}
	return((flg->flg_two == 1 || flg->flg_one == 1) ? FALSE : TRUE);
}

int main()
{
	t_all all;
	int i = check_quotes("a\"\'\"a",&all.flgs);
	printf("%d\n",i);
	
}