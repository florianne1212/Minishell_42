/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:55:11 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 22:21:32 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Alloue et retourne une chaine de caractères issue de la chaine ’s’. Cette
** nouvelle chaine commence à l’index ’start’ et a pour taille maximale ’len’
*/

#include "./includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new;
	unsigned long	i;

	if (!s)
		return (NULL);
	if (!(new = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	if (ft_strlen(s) < start)
	{
		new[i] = '\0';
		return (new);
	}
	while (s[i + start] && i < len)
	{
		new[i] = s[i + start];
		i++;
	}
	new[i] = '\0';
	return (new);
}
