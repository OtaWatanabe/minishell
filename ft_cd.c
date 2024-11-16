#include "ft_minishell.h"

char *exist_str(char **env, char *search, int len)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while(env[count] != NULL)
        count++;
    while(i < count)
    {
        if(ft_strncmp(env[i],search,len) == 0)
            return &env[i][len];
        i++;
    }
    return NULL;
}

int pwd_set(t_shell *shell , int flag)
{
    char *str;

    str = getcwd(NULL,0);
    if(str == NULL)
        error_exit("malloc");
    if(flag == 1)
        set_env(shell, "PWD", str);
    else if (flag == 2)
        set_env(shell, "OLDPWD", exist_str(shell->env_array,"PWD=",4));
    free(str);
    return 0;
}

    /*
        chdirで移動する。
        権限があるか、
        PATHが存在するか、
        HOMEが存在するか
        PWD OLDPATHを上書き、
    */

int chdir_set(t_shell *shell, char *path_str)
{
    if(chdir(path_str) != 0)
    {
        printf("cd: no such file or directory: %s\n",path_str);
        return 1;
    }
    if(exist_str(shell->env_array,"OLDPWD=",7))
        pwd_set(shell, 2);
    if(exist_str(shell->env_array,"PWD=",4))
        pwd_set(shell, 1);
    return 0;
}

int ft_cd(t_shell *shell, char **command)
{
    char *cd_str;
    
    if(command[1] == NULL || command[1][0] == '\0')
    {
        cd_str = exist_str(shell->env_array, "HOME=",5);
        if(cd_str == NULL)
            return 0;            
        chdir_set(shell, cd_str);
        return 0;
    }
    if(chdir_set(shell, command[1]) != 0)
        return 1;
    else if(access(command[1], R_OK) != 0)
		error_exit("access");
    else
        return 0;
    return 0;
}

