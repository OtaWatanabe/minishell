#include "ft_minishell.h"

int delete_words (char **env_array, char *str, int len)
{
    int i;

    i = 0;
    while(env_array[i] != NULL)
    {
        if(strncmp(env_array[i], str, len) == 0)
        {
            free(env_array[i]);
            env_array[i] = strdup("");
            if(env_array[i] == NULL)
                error_exit("malloc:");
            break ;
        }
        i++;
    }
    return 0;
}

// int ft_unset(char **env, char **command)
int ft_unset(t_shell *shell, char **command)
{
    /*
        unsetしたら空文字にする。
        t_shellの中のchar **env_arrayとchar **env_pathに入ってる。
        env_path には/Users/shucream/.rbenv/shimsが:に区切られてある。
        もともとメモリが用意されているのでそこの部分はfreeして新たにmallocして単語のメモリを確保
        env_arrayを探す。pathならifでそこも消す。

        env_arrayを探す。
        一致したら新しいメモリを確保してそこをfree
    */
    int i;

    i = 1;
    while(command[i] != NULL)
    {
        // delete_words(env, command[i], strlen(command[i]));  
        delete_words(shell->env_array, command[i], strlen(command[i]));
        if(strncmp(command[i],"PATH",5) == 0)
            delete_words(shell->env_path,command[i],strlen(command[i]));
        i++;
    }

    return 0;
}

// char **copy_env(char **env)
// {
//     int count = 0;
//     while (env[count] != NULL)
//         count++;

//     char **env_copy = (char **)malloc((count + 1) * sizeof(char *));
//     if (env_copy == NULL)
//     {
//         perror("malloc failed");
//         exit(EXIT_FAILURE);
//     }

//     for (int i = 0; i < count; i++)
//     {
//         env_copy[i] = strdup(env[i]);
//         if (env_copy[i] == NULL)
//         {
//             perror("strdup failed");
//             for (int j = 0; j < i; j++)
//                 free(env_copy[j]);
//             free(env_copy);
//             exit(EXIT_FAILURE);
//         }
//     }
//     env_copy[count] = NULL;

//     return env_copy;
// }

// int main(int ac, char **av, char **env)
// {
//     char **env_copy = copy_env(env);

//     for (int i = 0; env_copy[i] != NULL; i++)
//         printf("%s\n", env_copy[i]);

//     char **command;

//     command = (char **)malloc(4 * sizeof(char *)); // "unset", "HOME", "PATH", NULL の4つ
//     if (command == NULL)
//     {
//         perror("malloc failed");
//         return EXIT_FAILURE;
//     }

//     command[0] = strdup("unset");
//     command[1] = strdup("HOME");
//     command[2] = strdup("PATH");
//     command[3] = NULL;


//     ft_unset(env_copy,command);

//     int count;
//     int i;

//     i = 0;
//     count = 0;
//     while(env_copy[count] != NULL)
//         count++;
//     while(i < count)
//     {
//         printf("this is env :%s\n",env_copy[i]);
//         i++;
//     }
//     // メモリ解放
//     for (int i = 0; env_copy[i] != NULL; i++)
//         free(env_copy[i]);
//     free(env_copy);

//     return 0;
// }