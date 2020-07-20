/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 09:38:25 by fcoudert          #+#    #+#             */
/*   Updated: 2019/11/26 16:20:10 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	nbr_words(char const *s, char c)
{
	int		i;
	int		a;

	a = 0;
	i = 0;
	while (s && s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			a++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (a);
}

static char	*ft_strdup_split(const char *s1, char c)
{
	int		size_s1;
	char	*copy;
	int		i;

	i = 0;
	size_s1 = 0;
	while (s1[size_s1] != '\0' && s1[size_s1] != c)
	{
		size_s1++;
	}
	if (!(copy = malloc(sizeof(char) * (size_s1 + 1))))
		return (NULL);
	while (s1[i] != '\0' && s1[i] != c)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char		**ft_split(char const *s, char c)
{
	int		j;
	int		i;
	char	**tab1;

	j = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(tab1 = (char **)malloc(sizeof(char *) * (nbr_words(s, c) + 1))))
		return (0);
	while (j < nbr_words(s, c))
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != '\0' && s[i] != c)
		{
			tab1[j] = ft_strdup_split((s + i), c);
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		j++;
	}
	tab1[j] = 0;
	return (tab1);
}
