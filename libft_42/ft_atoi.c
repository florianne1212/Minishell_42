/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 09:50:18 by fcoudert          #+#    #+#             */
/*   Updated: 2019/11/25 15:16:58 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_isspace(char c)
{
	if ((c == ' ') || (c == '\f') ||
			(c == '\n') || (c == '\v') ||
			(c == '\r') || (c == '\t'))
		return (1);
	return (0);
}

int				ft_atoi(const char *str)
{
	long int	i;
	long int	resu;
	long int	sign;
	long int	test;

	i = 0;
	resu = 0;
	sign = 1;
	test = 0;
	while (str[i] != '\0' && ft_isspace(str[i]) == 1)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
		test++;
	}
	while ((str[i] != '\0') && (str[i] >= '0' && str[i] <= '9'))
		resu = resu * 10 + (str[i++] - '0');
	if (test > 1)
		return (0);
	return (sign * resu);
}
