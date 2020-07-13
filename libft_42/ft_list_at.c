/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 23:01:13 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 21:56:45 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Renvoie le n-ième élément de la liste, sachant que le premier élément est
** l’élément 0.
*/

#include "libft.h"

t_list	*ft_list_at(t_list *begin_list, unsigned int nbr)
{
	unsigned int	i;
	t_list			*count;

	i = 0;
	if (!begin_list)
		return (NULL);
	count = begin_list;
	while (count)
	{
		if (i == nbr)
			return (count);
		count = count->next;
		i++;
	}
	return (NULL);
}
