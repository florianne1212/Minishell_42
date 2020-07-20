/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:10:49 by fcoudert          #+#    #+#             */
/*   Updated: 2019/11/25 15:01:14 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned const char	*ch_s1;
	unsigned const char	*ch_s2;

	i = 0;
	ch_s1 = (unsigned const char *)s1;
	ch_s2 = (unsigned const char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (ch_s1[i] != ch_s2[i])
		{
			return (ch_s1[i] - ch_s2[i]);
		}
		i++;
	}
	return (0);
}
