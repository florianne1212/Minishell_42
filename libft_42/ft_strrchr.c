/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:43:50 by fcoudert          #+#    #+#             */
/*   Updated: 2019/11/25 15:06:05 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int a;

	a = 0;
	i = ft_strlen((char *)s);
	i--;
	if (c == '\0')
	{
		while (s[a] != '\0')
			a++;
		return ((char *)&s[a]);
	}
	while (i > 0 && s[i] != c)
		i--;
	if (s[i] == c)
		return ((char *)&s[i]);
	return (0);
}
