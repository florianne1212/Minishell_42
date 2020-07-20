/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 08:22:45 by fcoudert          #+#    #+#             */
/*   Updated: 2019/11/25 15:00:11 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ch_dst;
	unsigned char	*ch_src;

	ch_dst = (unsigned char *)dst;
	ch_src = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (ch_dst > ch_src)
	{
		while (len > 0)
		{
			len--;
			ch_dst[len] = ch_src[len];
		}
	}
	if (ch_src > ch_dst)
		ft_memcpy(dst, src, len);
	return (dst);
}
