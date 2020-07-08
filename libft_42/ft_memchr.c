/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:03:55 by fcoudert          #+#    #+#             */
/*   Updated: 2019/11/25 15:00:41 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*t;

	i = 0;
	t = (char *)s;
	while (i < n)
	{
		if (t[i] == c)
		{
			return ((void *)&t[i]);
		}
		i++;
	}
	return (0);
}
