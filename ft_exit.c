#include "ft_minishell.h"

int ft_exit(char **commands)
{
    int exit_status;
    int i;

    i = 1;
    while(commands[i] != NULL)
        i++;
    if(i > 1)
        error_exit("exit: too many arguments");
    exit_status = ft_atoi(commands[1]) % 256;
    return exit_status;
}