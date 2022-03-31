/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 19:34:33 by sarchoi           #+#    #+#             */
/*   Updated: 2021/05/11 12:09:59 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_nbrlen(int n)
{
	unsigned int count;
	unsigned int num;

	if (n == 0)
		return (1);
	count = n < 0 ? 1 : 0;
	num = n < 0 ? -n : n;
	while (num)
	{
		count++;
		num /= 10;
	}
	return (count);
}

static char			*return_zero(char *r)
{
	r = (char *)malloc(sizeof(char) * 2);
	r[0] = '0';
	r[1] = '\0';
	return (r);
}

char				*ft_itoa(int n)
{
	unsigned int	num;
	unsigned int	num_len;
	char			*r;

	r = NULL;
	if (n == 0)
		return (return_zero(r));
	num = n;
	if (n < 0)
		num *= -1;
	num_len = ft_nbrlen(n);
	r = (char *)malloc(num_len + 1);
	if (!r)
		return ((char *)0);
	r[num_len--] = '\0';
	while (num)
	{
		r[num_len--] = num % 10 + '0';
		num /= 10;
	}
	if (n < 0)
		r[num_len] = '-';
	return (r);
}
