/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 00:27:48 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 22:03:57 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Renvoie l’adresse du premier élément dont la donnée comparée à
** data_ref à l’aide de cmp, fait que cmp renvoie 0.
*/

#include "libft.h"

t_list	*ft_list_find(t_list *begin_list, void *content_ref, int (*cmp)())
{
	t_list	*new;

	new = begin_list;
	while (new)
	{
		if (!((*cmp)(new->content, content_ref)))
			return (new);
		new = new->next;
	}
	return (NULL);
}
