/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorted_list_merge.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:08:19 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 22:12:17 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Intègre les éléments d’une liste triée begin2 dans une autre liste triée
** begin1, de sorte que la liste begin1 reste triée par ordre croissant
*/

#include "libft.h"

static void	ft_sorted_list_insert2(t_list **begin_list, t_list *elem,
				int (*cmp)())
{
	t_list *list;

	list = *begin_list;
	if ((!(*begin_list)) || ((*cmp)(list->content, elem->content) > 0))
	{
		elem->next = *begin_list;
		*begin_list = elem;
		return ;
	}
	while (list->next)
	{
		if (((*cmp)(list->next->content, elem->content) > 0))
		{
			elem->next = list->next;
			list->next = elem;
			return ;
		}
		list = list->next;
	}
	list->next = elem;
}

void		ft_sorted_list_merge(t_list **begin_list1, t_list *begin_list2,
				int (*cmp)())
{
	t_list	*list2;
	t_list	*elem;

	list2 = begin_list2;
	while (list2)
	{
		elem = list2;
		list2 = list2->next;
		elem->next = NULL;
		ft_sorted_list_insert2(begin_list1, elem, (*cmp));
	}
}
