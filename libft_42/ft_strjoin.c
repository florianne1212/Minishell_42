/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:11:13 by fcoudert          #+#    #+#             */
/*   Updated: 2019/11/26 10:38:49 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	ss1;
	size_t	ss2;
	char	*s3;

	if (s1)
	{
		i = 0;
		j = 0;
		ss1 = ft_strlen((char *)s1);
		ss2 = ft_strlen((char *)s2);
		if (!(s3 = malloc(sizeof(char) * (ss1 + ss2 + 1))))
			return (0);
		while (i < (ss1))
		{
			s3[i] = s1[i];
			i++;
		}
		while (j < (ss2))
			s3[i++] = s2[j++];
		s3[i] = '\0';
		return (s3);
	}
	return (NULL);
}
