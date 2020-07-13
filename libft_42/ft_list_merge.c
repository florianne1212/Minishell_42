/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 18:19:02 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 22:06:37 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Met les éléments d’une liste begin2 à la fin d’une autre liste begin1
*/

#include "libft.h"

void	ft_list_merge(t_list **begin_list1, t_list *begin_list2)
{
	t_list *new;

	if (!(*begin_list1))
	{
		*begin_list1 = begin_list2;
		return ;
	}
	new = *begin_list1;
	while (new && new->next)
		new = new->next;
	new->next = begin_list2;
}
