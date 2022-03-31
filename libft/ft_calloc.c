/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:57:04 by sarchoi           #+#    #+#             */
/*   Updated: 2021/05/09 12:30:46 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*r;

	if (size && count > (size_t)(-1 / size))
		return ((void *)0);
	r = malloc(count * size);
	if (!r)
		return ((void *)0);
	if (r)
		ft_bzero(r, count * size);
	return (r);
}
