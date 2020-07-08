/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:56:44 by fcoudert          #+#    #+#             */
/*   Updated: 2019/11/27 11:08:28 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char const *set, char c)
{
	int		i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	set_beginning(char const *str, char const *set)
{
	int		i;

	i = 0;
	while (isset(set, str[i]) == 1)
		i++;
	return (i);
}

static int	set_end(char const *str, char const *set)
{
	int		i;

	i = (ft_strlen(str) - 1);
	while (isset(set, str[i]) == 1 && i > 0)
		--i;
	return (i);
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	a;
	size_t	c;
	char	*trim_s1;

	if (s1)
	{
		a = 0;
		i = set_beginning(s1, set);
		j = set_end(s1, set);
		c = j - i;
		if (i == ft_strlen((char *)s1))
			return (ft_strdup(""));
		if (!(trim_s1 = malloc(sizeof(char) * (c + 2))))
			return (0);
		while (i <= j)
			trim_s1[a++] = s1[i++];
		trim_s1[a] = '\0';
		return (trim_s1);
	}
	return (NULL);
}
