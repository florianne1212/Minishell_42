/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 13:27:05 by fcoudert          #+#    #+#             */
/*   Updated: 2019/11/26 11:00:24 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		j;
	char	*new_s;

	if (s)
	{
		i = 0;
		j = ft_strlen((char *)s);
		if (!(new_s = malloc(sizeof(char) * j + 1)))
			return (0);
		if (new_s == NULL)
			return (NULL);
		while (s[i] != '\0')
		{
			new_s[i] = f(i, s[i]);
			i++;
		}
		new_s[i] = '\0';
		return (new_s);
	}
	return (NULL);
}
