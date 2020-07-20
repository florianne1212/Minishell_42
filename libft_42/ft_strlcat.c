/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:32:49 by fcoudert          #+#    #+#             */
/*   Updated: 2019/11/25 15:08:21 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	size_s;
	size_t	size_d;

	i = 0;
	size_s = ft_strlen(src);
	size_d = ft_strlen(dst);
	if ((dstsize - 1) < size_d)
		return (size_s + dstsize);
	if (dstsize == 0)
		return (size_s);
	while ((size_d + i) < (dstsize - 1) && (dstsize > 0) && src[i] != '\0')
	{
		dst[size_d + i] = src[i];
		i++;
	}
	dst[size_d + i] = '\0';
	return (size_d + size_s);
}
