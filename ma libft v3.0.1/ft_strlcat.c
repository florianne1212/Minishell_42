/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:44:46 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/01/31 11:02:21 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	dstlength;

	i = 0;
	dstlength = ft_strlen(dst);
	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	while (src[i] && dstlength + i < dstsize - 1)
	{
		dst[dstlength + i] = src[i];
		i++;
	}
	dst[dstlength + i] = '\0';
	return (ft_strlen(src) + dstlength);
}
