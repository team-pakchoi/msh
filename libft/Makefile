CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a
GNL	 = get_next_line.c get_next_line_utils.c
SRCS = $(addprefix gnl/, $(GNL)) \
	ft_memset.c ft_bzero.c \
	ft_strlen.c ft_strlcpy.c ft_strchr.c \
	ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c \
	ft_isalpha.c ft_isdigit.c \
	ft_calloc.c ft_strdup.c ft_strndup.c\
	ft_strjoin.c ft_strtrim.c \
	ft_split.c ft_itoa.c \
	ft_putchar_fd.c ft_putstr_fd.c \
	ft_strarr_len.c ft_strarr_lcpy.c ft_strarr_join.c ft_strarr_shift.c \
	ft_free_arr.c
OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	ar -cr $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
