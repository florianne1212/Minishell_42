/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 09:11:47 by fcoudert          #+#    #+#             */
/*   Updated: 2019/11/26 09:07:55 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			e;
	char			*copy;

	e = 0;
	i = start;
	if (s == NULL)
		return (NULL);
	if (start > ((unsigned int)ft_strlen((char *)s)))
		return (ft_strdup(""));
	if (!(copy = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (e < (len) && s[i] != '\0')
	{
		copy[e] = s[i];
		i++;
		e++;
	}
	copy[e] = '\0';
	return (copy);
}
