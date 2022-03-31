/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:56:54 by sarchoi           #+#    #+#             */
/*   Updated: 2021/05/11 12:05:51 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	unsigned int	r;
	int				sign;

	r = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		if (((int)r * sign) > 469762049)
			return (-1);
		else if (((int)r * sign) < -469762049)
			return (0);
		else
			r = r * 10 + (*str - '0');
		str++;
	}
	return (r * sign);
}
