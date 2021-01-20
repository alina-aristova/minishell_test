//
// Created by Benita Hankey on 1/12/21.
//

#ifndef MINISHELL_MINISHELL_H
# define MINISHELL_MINISHELL_H

# include "build-in_functions.h"
# include "exit.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

char *env_finder(char *key, char **env);


#endif
