/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:56:44 by fcoudert          #+#    #+#             */
/*   Updated: 2020/09/07 18:27:52 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isinset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	unsigned int		count;
	unsigned int		start;
	unsigned int		i;

	if (!s1)
		return (NULL);
	i = 0;
	start = 0;
	count = ft_strlen(s1);
	while (isinset(s1[i], set) && s1[i])
		i++;
	if (i == count)
		return (ft_substr(s1, start, 0));
	start = i;
	count = count - i;
	i = ft_strlen(s1) - 1;
	while (isinset(s1[i], set))
	{
		i--;
		count--;
	}
	return (ft_substr(s1, start, count));
}
