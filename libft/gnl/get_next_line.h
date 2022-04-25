/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:06:39 by cpak              #+#    #+#             */
/*   Updated: 2022/04/25 00:10:28 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# define BUFFER_SIZE 10

typedef struct s_line
{
	char			**line;
	int				idx;
	int				size;
}					t_line;

typedef struct s_memo
{
	char			*str;
	int				fd;
	int				idx;
	int				size;
	int				isdone;
	struct s_memo	*next;
}					t_memo;

int	gnl_strcpy(char *dst, char *src, int *start_idx, int size);
int	gnl_realloc(char **old, int new_size, int old_size);
int	line_overflow(t_line **tline, int total_size);
int	init_struct(t_line **tline, t_memo **tmemo, char **line, int fd);
int	get_next_line(int fd, char **line);

#endif
