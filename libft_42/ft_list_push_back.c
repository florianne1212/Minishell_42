/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 02:13:04 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 21:47:54 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  Ajoute à la fin de la liste un nouvel élément de type t_list.
*/

#include "libft.h"

void	ft_list_push_back(t_list **begin_list, void *content)
{
	t_list	*new;
	t_list	*last;

	if (!(new = ft_create_elem(content)))
		exit(EXIT_FAILURE);
	if (!(*begin_list))
		*begin_list = new;
	else
	{
		last = ft_list_last(*begin_list);
		last->next = new;
	}
}
