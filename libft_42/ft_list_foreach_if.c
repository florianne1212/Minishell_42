/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 23:24:03 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 22:01:37 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Applique une fonction donnée en paramètre à la valeur contenue dans
** certains éléments de la liste • f n'est appliqué que sur les éléments
** qui passé en argument à cmp avec data_ref, cmp renvoie 0
*/

#include "libft.h"

void	ft_list_foreach_if(t_list *begin_list, void (*f)(void *), void
	*content_ref, int (*cmp)())
{
	t_list *begin;

	begin = begin_list;
	if (!(begin))
		return ;
	while (begin)
	{
		if (!((*cmp)(begin->content, content_ref)))
			(*f)(begin->content);
		begin = begin->next;
	}
}
