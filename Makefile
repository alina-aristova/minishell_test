# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/31 01:59:37 by bhankey           #+#    #+#              #
#    Updated: 2020/10/31 01:59:39 by bhankey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c

NAME	=	minishell

OBJS	=	$(SRCS:.c=.o)

CC		=	clang

CFLAGS	=	-Wall -Wextra -Werror -I ./includes -I ./libft

all:		$(NAME)

$(NAME):	$(OBJS)
			$(MAKE) bonus -C libft
			$(CC) $(CFALGS) -o $(NAME) $(OBJS) -O3 ./libft/libft.a

clean:
			rm -f $(OBJS)
			$(MAKE) clean -C libft

fclean:		clean
			$(MAKE) fclean -C libft
			rm -f $(NAME)

re:			fclean all

.PHONY: 	all clean fclean re