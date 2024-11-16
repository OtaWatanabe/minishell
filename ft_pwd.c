#include "ft_minishell.h"

int ft_pwd ()
{
    /*
        getcwd(NULL,0)を指定すると現在のディレクトリの位置がmallocで確保されたchar配列が返る。
        そいつをprintfすればいい。
    */
    char *buf;

    buf = getcwd(NULL, 0);
    if(buf == NULL)
        return 1;
    else
    {
        printf("%s\n",buf);
        free(buf);
    }
    return 0;

}

