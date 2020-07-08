/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 08:15:55 by fcoudert          #+#    #+#             */
/*   Updated: 2019/11/25 15:18:50 by fcoudert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t count, size_t size)
{
	void	*tab;

	if (!(tab = malloc(size * count)))
		return (NULL);
	ft_bzero(tab, count * size);
	return (tab);
}
