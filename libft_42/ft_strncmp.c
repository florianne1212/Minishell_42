/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:41:43 by fcoudert          #+#    #+#             */
/*   Updated: 2019/11/25 15:18:19 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int						ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	unsigned const char	*ch_s1;
	unsigned const char	*ch_s2;

	i = 0;
	ch_s1 = (const unsigned char *)s1;
	ch_s2 = (const unsigned char *)s2;
	if (n == 0)
	{
		return (0);
	}
	while (ch_s1[i] != '\0' && ch_s1[i] != '\0' && i < n)
	{
		if (ch_s1[i] != ch_s2[i])
		{
			return (ch_s1[i] - ch_s2[i]);
		}
		i++;
	}
	if (i < n)
	{
		return (ch_s1[i] - ch_s2[i]);
	}
	return (0);
}
