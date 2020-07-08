/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:47:57 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/01/31 11:02:21 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*s1;
	const char	*s2;

	i = 0;
	s1 = dst;
	s2 = src;
	if (src > dst)
		while (i < len)
		{
			s1[i] = s2[i];
			i++;
		}
	else if (src < dst)
		while (len--)
			s1[len] = s2[len];
	return (dst);
}
