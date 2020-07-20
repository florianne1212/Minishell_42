/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 18:45:07 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 22:08:23 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Trie par ordre croissant le contenu de la liste, en comparant deux éléments
** grâce à une fonction de comparaison de données des deux éléments
*/

#include "libft.h"

void	ft_list_sort(t_list **begin_list, int (*cmp)())
{
	t_list	*list1;
	t_list	*list2;
	void	*temp;

	if (!(*begin_list) || !((*begin_list)->next))
		return ;
	list1 = *begin_list;
	while (list1 && list1->next)
	{
		list2 = list1->next;
		while (list2)
		{
			if (((*cmp)(list1->content, list2->content)) > 0)
			{
				temp = list2->content;
				list2->content = list1->content;
				list1->content = temp;
			}
			list2 = list2->next;
		}
		list1 = list1->next;
	}
}
