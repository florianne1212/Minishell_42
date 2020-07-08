/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:44:28 by fcoudert          #+#    #+#             */
/*   Updated: 2019/11/25 15:14:52 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t b;

	b = 0;
	i = 0;
	if (needle[b] == '\0')
	{
		return ((char *)haystack);
	}
	while (haystack[i] != '\0')
	{
		while (haystack[i + b] == needle[b] && i + b < len)
		{
			b++;
			if (needle[b] == '\0')
			{
				return ((char *)&haystack[i]);
			}
		}
		b = 0;
		i++;
	}
	return (0);
}
