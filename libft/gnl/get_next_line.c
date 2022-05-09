/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 15:46:40 by cpak              #+#    #+#             */
/*   Updated: 2022/05/04 22:49:57 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_memo(t_line **tline, t_memo **tmemo, int fd)
{
	t_memo		*p_tmemo;
	int			result;
	int			size;

	p_tmemo = *tmemo;
	while (p_tmemo->fd != fd)
		p_tmemo = p_tmemo->next;
	size = p_tmemo->size - p_tmemo->idx;
	if (line_overflow(&(*tline), size) == -1)
		return (-1);
	result = gnl_strcpy(
			*(*tline)->line,
			(p_tmemo->str + p_tmemo->idx),
			&(*tline)->idx, size);
	if (result == 1)
		p_tmemo->idx += ((*tline)->idx + 1);
	else if (result == 2)
	{
		p_tmemo->str[0] = 0;
		p_tmemo->idx = 0;
		p_tmemo->size = 0;
	}
	return (result);
}

static void	memo_line(t_memo **tmemo, char *src, int fd)
{
	t_memo	*p_tmemo;
	int		i;
	int		j;

	p_tmemo = *tmemo;
	while (p_tmemo->fd != fd)
		p_tmemo = p_tmemo->next;
	i = 0;
	j = 0;
	while (src[i] && src[i] != '\n')
		i++;
	i++;
	while (src[i] && i < BUFFER_SIZE)
		p_tmemo->str[j++] = src[i++];
	p_tmemo->str[j] = 0;
	p_tmemo->size = j;
}

static int	get_new_buf(int *fd, t_line *tline, t_memo **tmemo)
{
	char	*tmp_buf;
	int		result;

	result = 2;
	tmp_buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!tmp_buf)
		return (-1);
	while (result == 2)
	{
		result = read(*fd, tmp_buf, BUFFER_SIZE);
		if (result == -1)
			break ;
		tmp_buf[result] = 0;
		if (result)
		{
			line_overflow(&tline, tline->idx + result);
			result = gnl_strcpy(*tline->line, tmp_buf,
					&tline->idx, BUFFER_SIZE);
		}
		if (result != 2)
			memo_line(tmemo, tmp_buf, *fd);
	}
	free(tmp_buf);
	return (result);
}

static void	check_and_free_memo(t_memo **tmemo, int fd)
{
	t_memo		*next_tmemo;
	int			all_is_done;

	all_is_done = 1;
	next_tmemo = *tmemo;
	while (next_tmemo)
	{
		if (next_tmemo->fd == fd)
			next_tmemo->isdone = 1;
		else if (next_tmemo->isdone == 0)
			all_is_done = 0;
		next_tmemo = next_tmemo->next;
	}
	next_tmemo = *tmemo;
	while (next_tmemo && all_is_done == 1)
	{
		*tmemo = next_tmemo;
		next_tmemo = (*tmemo)->next;
		free((*tmemo)->str);
		free(*tmemo);
		*tmemo = 0;
	}
}

int	get_next_line(int fd, char **line)
{
	int					result;
	static t_memo		*tmemo;
	t_line				*tline;

	if (line == 0 || BUFFER_SIZE < 1 || fd < 0 || fd > 256)
		return (-1);
	if (init_struct(&tline, &tmemo, line, fd) == -1)
		return (-1);
	result = check_memo(&tline, &tmemo, fd);
	if (result == 2)
		result = get_new_buf(&fd, tline, &tmemo);
	if (gnl_realloc(tline->line, tline->idx, tline->idx) == -1)
		return (-1);
	if (result == 0)
		check_and_free_memo(&tmemo, fd);
	free(tline);
	return (result);
}
