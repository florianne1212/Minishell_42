/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 07:21:52 by fcoudert          #+#    #+#             */
/*   Updated: 2019/11/25 15:00:16 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*ch_src;
	char	*ch_dest;

	i = 0;
	ch_src = (char *)src;
	ch_dest = (char *)dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		ch_dest[i] = ch_src[i];
		i++;
	}
	return (dst);
}
