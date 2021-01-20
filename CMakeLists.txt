cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS_MINSIZEREL "-Wall -Wextra -Werror")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-Wall -Wextra -Werror")
set(CMAKE_C_FLAGS_RELEASE "-Wall -Wextra -Werror")
include_directories(libft includes gnl)
add_executable(minishell main.c libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_itoa.c
        libft/ft_memccpy.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c
        libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c
        libft/ft_strmapi.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c libft/ft_split.c
        envp/env_finder.c build-in_functions/echo.c includes/build-in_functions.h build-in_functions/pwd.c exit_functions/exit_malloc.c includes/exit.h "build-in_functions/cd.c" envp/reallocate_envp.c libft/size_of_2d_array.c libft/clear_2d_arr.c)