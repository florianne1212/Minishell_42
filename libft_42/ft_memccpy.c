/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:06:45 by fcoudert          #+#    #+#             */
/*   Updated: 2019/11/14 10:07:01 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*ch_dst;
	unsigned char	*ch_src;
	unsigned char	t;

	i = 0;
	t = (unsigned char)c;
	ch_dst = (unsigned char *)dst;
	ch_src = (unsigned char *)src;
	while (i < n)
	{
		ch_dst[i] = ch_src[i];
		if (ch_src[i] == t)
		{
			return ((void *)&ch_dst[i + 1]);
		}
		i++;
	}
	return (0);
}
