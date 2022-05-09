# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 19:18:15 by sarchoi           #+#    #+#              #
#    Updated: 2022/05/09 16:17:32 by sarchoi          ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS_ROOT = main.c prompt.c command.c signal.c
SRCS_BUILTIN = cd.c echo.c env.c exit.c export.c pwd.c unset.c
SRCS_EXEC = assign.c command.c heredoc.c redirection.c
SRCS_PARSING = cmd.c env_1.c env_2.c sep.c split.c
SRCS_UTIL = cd.c cmd.c export.c fd_1.c fd_2.c \
	history.c print.c quote.c var_1.c var_2.c
SRCS = $(addprefix ./src/, $(SRCS_ROOT)) \
	$(addprefix ./src/builtin/, $(SRCS_BUILTIN)) \
	$(addprefix ./src/exec/, $(SRCS_EXEC)) \
	$(addprefix ./src/parsing/, $(SRCS_PARSING)) \
	$(addprefix ./src/util/, $(SRCS_UTIL))

OBJS = $(SRCS:.c=.o)

LIBFT = libft
LIBFT_FLAGS = -l ft -L ./$(LIBFT)
READLINE_FLAGS = -l readline -L /usr/local/opt/readline/lib

INC_FLAGS = -I includes -I $(LIBFT) -I /usr/local/opt/readline/include

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
	@make all --silent --directory=$(LIBFT)
	$(info $(green)<MAKE> Libft - make$(reset))

clean:
	@rm -f $(OBJS)
	@rm -f result.txt result_*.diff
	$(info $(green)<MAKE> clean$(reset))
	@make clean --silent --directory=$(LIBFT)
	$(info $(green)<MAKE> Libft - clean$(reset))

fclean: clean
	@rm -f $(NAME)
	$(info $(green)<MAKE> fclean$(reset))
	@make fclean --silent --directory=$(LIBFT)
	$(info $(green)<MAKE> Libft - fclean$(reset))

re: fclean all
	$(info $(red)<MAKE> re$(reset))

test: $(NAME)
	$(info $(green)<MAKE> test$(reset))
	./test/test.sh
	$(info $(green)<MAKE> test - Complete! Check `result_` files$(reset))

.PHONY: all clean fclean re test $(LIBFT) $(NAME)
