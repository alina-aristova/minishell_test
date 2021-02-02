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

	char	**argv;
	t_reds 	*reds_right;
	t_reds 	*reds_left;
	int output;
	int input;
	
}				t_shell;
typedef struct	s_flgs
{
	int flg_two;
	int *len_right_r;
	int *en_left_r;
	int count_sem;
	int *count_pipe;

	int flg_one;
}			t_flgs;
typedef struct	s_all
{
	t_shell **shell;
	t_flgs flgs;
}			t_all;

char			**update_split(char const *s, char c);

#endif