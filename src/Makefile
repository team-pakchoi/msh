# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 19:18:15 by sarchoi           #+#    #+#              #
#    Updated: 2022/05/11 06:42:11 by cpak             ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re test $(LIBFT) $(NAME)

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS_ROOT = main.c prompt.c command.c command_multi.c signal.c
SRCS_BUILTIN = cd.c echo.c env.c exit.c export.c pwd.c unset.c
SRCS_EXEC = assign.c builtin.c execve.c heredoc.c redirection.c
SRCS_PARSING = cmd.c env.c parse_cmd.c parse_str.c sep.c split.c
SRCS_UTIL = cd.c cmd.c exit.c export.c fd_1.c fd_2.c \
	history.c print.c quote.c var_1.c var_2.c
SRCS = $(SRCS_ROOT) \
	$(addprefix ./builtin/, $(SRCS_BUILTIN)) \
	$(addprefix ./exec/, $(SRCS_EXEC)) \
	$(addprefix ./parsing/, $(SRCS_PARSING)) \
	$(addprefix ./util/, $(SRCS_UTIL))

OBJS = $(SRCS:.c=.o)

LIBFT = ../libft/libft.a
LIBFT_FLAGS = -l ft -L ../libft
READLINE_FLAGS = -l readline -L $(shell brew --prefix readline)/lib

INC_FLAGS = -I includes -I $(LIBFT) -I $(shell brew --prefix readline)/include

green:=$(shell tput setaf 2)
reset:=$(shell tput sgr0)

all: $(NAME)

$(NAME): $(OBJS)
	make $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT_FLAGS) $(READLINE_FLAGS)
	$(info $(green)<MAKE> NAME$(reset))

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_FLAGS)
	$(info $(green)<MAKE> $(<) -> $(@)$(reset))

$(LIBFT):
	@make -C ../libft
	$(info $(green)<MAKE> Libft - make$(reset))

clean:
	@rm -f $(OBJS)
	@rm -f result.txt result_*.diff
	$(info $(green)<MAKE> clean$(reset))
	@make clean --silent --directory=../libft
	$(info $(green)<MAKE> Libft - clean$(reset))

fclean: clean
	@rm -f $(NAME)
	$(info $(green)<MAKE> fclean$(reset))
	@make fclean --silent --directory=../libft
	$(info $(green)<MAKE> Libft - fclean$(reset))

re: fclean all
	$(info $(red)<MAKE> re$(reset))

test: $(NAME)
	$(info $(green)<MAKE> test$(reset))
	./test/test.sh
	$(info $(green)<MAKE> test - Complete! Check `result_` files$(reset))


