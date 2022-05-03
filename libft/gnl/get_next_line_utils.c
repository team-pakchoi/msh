/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:26:22 by cpak              #+#    #+#             */
/*   Updated: 2022/05/03 18:01:02 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strcpy(char *dst, char *src, int *start_idx, int size)
{
	int		i;

	if (size == 0)
		return (2);
	i = 0;
	while (src[i] && src[i] != '\n' && i < size)
	{
		dst[*start_idx] = src[i];
		*start_idx += 1;
		i += 1;
	}
	if (src[i] == '\n' && src[i] && i < size)
	{
		dst[*start_idx] = src[i];
		*start_idx += 1;
		i += 1;
		dst[*start_idx] = 0;
		return (1);
	}
	dst[*start_idx] = 0;
	if (src[i] == 0 && i < size)
		return (0);
	return (2);
}

int	gnl_realloc(char **old, int old_size, int new_size)
{
	char	*new;
	int		idx;

	idx = 0;
	new = (char *)malloc(sizeof(char) * new_size + 1);
	if (!new)
		return (-1);
	if (new_size == 0)
		new[0] = 0;
	else
		gnl_strcpy(new, *old, &idx, old_size);
	free(*old);
	*old = new;
	return (1);
}

int	line_overflow(t_line **tline, int total_size)
{
	int			*p_size;
	char		**p_line;

	p_size = &(*tline)->size;
	p_line = (*tline)->line;
	while (total_size >= *p_size)
	{
		*p_size *= 10;
		if (gnl_realloc(p_line, *p_size / 10, *p_size) == -1)
			return (-1);
	}
	return (1);
}

static int	init_memo(t_memo **tmemo, t_memo **prev, t_memo **next, int fd)
{
	if (!*next)
	{
		if (!*tmemo)
		{
			*tmemo = malloc(sizeof(t_memo));
			*next = *tmemo;
		}
		else
		{
			(*prev)->next = malloc(sizeof(t_memo));
			*next = (*prev)->next;
		}
		if (!*next)
			return (-1);
		(*next)->str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(*next)->str)
			return (-1);
		(*next)->str[0] = 0;
		(*next)->fd = fd;
		(*next)->idx = 0;
		(*next)->size = 0;
		(*next)->next = 0;
		(*next)->isdone = 0;
	}
	return (1);
}

int	init_struct(t_line **tline, t_memo **tmemo, char **line, int fd)
{
	t_memo		*prev_tmemo;
	t_memo		*next_tmemo;

	*tline = malloc(sizeof(t_line));
	if (!*tline)
		return (-1);
	*line = (char *)malloc(sizeof(char) * 101);
	if (!*line)
		return (-1);
	(*tline)->line = line;
	(*tline)->idx = 0;
	(*tline)->size = 100;
	prev_tmemo = *tmemo;
	next_tmemo = *tmemo;
	while (next_tmemo && next_tmemo->fd != fd)
	{
		prev_tmemo = next_tmemo;
		next_tmemo = prev_tmemo->next;
	}
	init_memo(tmemo, &prev_tmemo, &next_tmemo, fd);
	return (1);
}
