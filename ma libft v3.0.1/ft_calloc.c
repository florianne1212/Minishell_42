/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 09:43:46 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/01/31 10:59:58 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	if (!(ptr = malloc(size * count)))
		return (NULL);
	i = 0;
	while (i < (count * size))
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
