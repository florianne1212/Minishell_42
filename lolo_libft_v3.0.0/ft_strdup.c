/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:51:24 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/01/31 11:02:21 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*cpy;

	i = 0;
	len = 0;
	while (s1[len])
		len++;
	if (!(cpy = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i <= len)
	{
		cpy[i] = s1[i];
		i++;
	}
	return (cpy);
}
