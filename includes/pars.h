#ifndef PARS_H
# define PARS_H

# include "../libft/libft.h"
#define TRUE 1
#define FALSE 0
#define ERROR -1
typedef struct	s_reds
{
	int		flg;
	char	*red;
}				t_reds;

typedef struct	s_shell
{
	char	*command;
	char	**argv;
	t_reds 	*reds_right;
	t_reds 	*reds_left;
	int		pipe;
	
}				t_shell;
typedef struct	s_flgs
{
	int flg_two;
	int flg_one;
}			t_flgs;
typedef struct	s_all
{
	t_flgs flgs;
}			t_all;

#endif