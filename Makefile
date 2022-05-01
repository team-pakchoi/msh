# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 19:18:15 by sarchoi           #+#    #+#              #
#    Updated: 2022/04/30 03:25:58 by cpak             ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

# TODO: edit wildcard to src files
SRCS = $(wildcard src/*.c) $(wildcard src/*/*.c)
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

.PHONY: all clean fclean re $(LIBFT) $(NAME)
