/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 22:35:12 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 21:41:05 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Ajoute au début de la liste un nouvelélément de type t_list.
*/

#include "libft.h"

void	ft_list_push_front(t_list **begin_list, void *content)
{
	t_list	*new;

	if (!(new = ft_create_elem(content)))
		exit(EXIT_FAILURE);
	new->next = *begin_list;
	*begin_list = new;
}
