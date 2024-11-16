#include "ft_minishell.h"


void space_words_print(char **word, int newlineflag)
{
    int i;

    i = 0;
    while(word[i] != NULL)
    {
        if(i == 0)
            printf("%s",word[i]);
        else
            printf(" %s",word[i]);
        i++;
    }
    if(newlineflag == 0)
        printf("\n");
}

int has_option(char **commands)
{
    if(strncmp(commands[1],"-n",3) == 0)
        return 1;
    return 0;
}

int is_option(char *commands)
{
    /*
       単語がオプションか？文字列の最初に-がついてるかのジャッジだけ。 
       -nnnnnとかのnだけならok
       -nnnnaとかn以外が入ってると文字列判定
       return 1で文字列判定をする。
    */
    int i;

    i = 1;
    if(commands[0] != '-')
        return 1;
    while(commands[i] != '\0')//ここで単語自体を判断した方がいい
    {
        if(commands[i] != 'n')
            return 1;
        i++;
    }
    return 0;
}

int ft_echo(char **command)
{
    /*
        重要なのは改行する出力か否か、とオプションか文字列かの判定。
        コマンドの単語群の
        command[1以降][]がオプションかコマンド引数なのかの判定
        文字列判定が出たならそれ以降はすべて文字として出力。 
        はじめは文字列判定、そこからオプションで-nnnでオプションフラグが立つ。
    */
    int newlineflag;
    int i;

    newlineflag = 0;
    i = 1;

    newlineflag = has_option(command);
    while(command[i] != NULL)
    {
        if(is_option(command[i]) == 1)
            break ;
        i++;
    }
    space_words_print(&command[i],newlineflag);
    return 0;
}

// int main(int ac, char **av)
// {
//     av++;
//     ft_echo(av);
// }