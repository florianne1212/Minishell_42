/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 23:37:08 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 21:57:52 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  Inverse l’ordre des éléments de la liste.
*/

#include "libft.h"

void	ft_list_reverse(t_list **begin_list)
{
	t_list *new;
	t_list *temp;
	t_list *begin;

	new = NULL;
	temp = NULL;
	begin = *begin_list;
	if (!(*begin_list))
		return ;
	while (begin)
	{
		temp = begin->next;
		begin->next = new;
		new = begin;
		begin = temp;
	}
	*begin_list = new;
}
