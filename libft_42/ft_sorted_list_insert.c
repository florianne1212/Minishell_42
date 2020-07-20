/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorted_list_insert.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 00:17:29 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 22:10:29 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Crée un nouvel élément et l’insère dans une liste triée de sorte que la liste
** reste triée par ordre croissant.
*/

#include "libft.h"

void	ft_sorted_list_insert(t_list **begin_list, void *content, int (*cmp)())
{
	t_list *new;
	t_list *list;

	list = *begin_list;
	if ((!(*begin_list)) || ((*cmp)(list->content, content) > 0))
	{
		ft_list_push_front(begin_list, content);
		return ;
	}
	while (list->next)
	{
		if (((*cmp)(list->next->content, content) > 0))
		{
			new = ft_create_elem(content);
			new->next = list->next;
			list->next = new;
			return ;
		}
		list = list->next;
	}
	new = ft_create_elem(content);
	list->next = new;
}
