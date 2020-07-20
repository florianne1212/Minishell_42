/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 21:57:03 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 21:52:40 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Retire et libère l’ensemble des éléments de la liste
*/

#include "libft.h"

void	ft_list_clear(t_list *begin_list, void (*free_fct)(void *))
{
	t_list	*temp;

	if (!begin_list)
		return ;
	while (begin_list)
	{
		temp = begin_list;
		if (free_fct)
			free_fct(temp->content);
		begin_list = begin_list->next;
		free(temp);
	}
}
