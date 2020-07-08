/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:59:01 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 22:24:35 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Alloue et retourne une copie de la chaine ’s1’, sans les caractères spécifiés
** dans ’set’ au début et à la fin de la chaine de caractères.
*/

#include "./includes/libft.h"

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
