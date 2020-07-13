/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 14:52:19 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 22:05:00 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Efface de la liste tous les éléments dont la donnée comparée à
** data_ref à l’aide de cmp, fait que cmp renvoie 0.
*/

#include "libft.h"

static void	free_elem(t_list *elem, void (*free_fct)(void *))
{
	t_list	*temp;

	temp = elem;
	if (*free_fct)
		(*free_fct)(temp->content);
	free(temp);
}

void		ft_list_remove_if(t_list **begin_list, void *content_ref,
				int (*cmp)(), void (*free_fct)(void *))
{
	t_list	*temp;
	t_list	*new;

	while ((*begin_list) && !((*cmp)((*begin_list)->content, content_ref)))
	{
		temp = *begin_list;
		*begin_list = temp->next;
		free_elem(temp, free_fct);
	}
	new = *begin_list;
	while (new)
	{
		temp = new->next;
		while (temp && !((*cmp)(temp->content, content_ref)))
		{
			new->next = temp->next;
			free_elem(temp, free_fct);
			temp = new->next;
		}
		new = new->next;
	}
}
