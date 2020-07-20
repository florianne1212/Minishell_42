/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 22:35:13 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 21:58:56 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Applique une fonction donnée en paramètre à la valeur contenue dans chaque
** élément de la liste.
*/

#include "libft.h"

void	ft_list_foreach(t_list *begin_list, void (*f)(void *))
{
	t_list	*list_ptr;

	if (!(begin_list))
		return ;
	list_ptr = begin_list;
	while (list_ptr)
	{
		(*f)(list_ptr->content);
		list_ptr = list_ptr->next;
	}
}
