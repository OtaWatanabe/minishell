# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 19:01:00 by otawatanabe       #+#    #+#              #
#    Updated: 2024/11/18 17:10:43 by otawatanabe      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -lreadline -Wno-unused-command-line-argument
CC = cc
SRCS = main.c execute.c access.c error.c heredoc.c get_next_line.c get_next_line_utils.c lexer.c free.c get_input.c files.c redirect.c env.c init.c expand.c list.c parser.c expand_helper.c env_helper.c signal.c ft_builtins.c ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c heredoc_helper.c execute_helper.c
NAME = minishell
OBJS = $(SRCS:.c=.o)
LIB = libft/libft.a
all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $^ $(LIB) -o $@

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re bonus