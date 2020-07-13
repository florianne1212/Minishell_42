/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_reverse_fun.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 19:25:18 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 22:09:20 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  Inverse l’ordre des éléments de la liste
*/

#include "libft.h"

static int		ft_list_size2(t_list *begin_list)
{
	int count;

	count = 0;
	while (begin_list)
	{
		begin_list = begin_list->next;
		count++;
	}
	return (count);
}

static t_list	*ft_list_at2(t_list *begin_list, unsigned int nbr)
{
	unsigned int	i;
	t_list			*count;

	i = 0;
	if (!begin_list)
		return (NULL);
	count = begin_list;
	while (count)
	{
		if (i == nbr)
			return (count);
		count = count->next;
		i++;
	}
	return (NULL);
}

void			ft_list_reverse_fun(t_list *begin_list)
{
	int		count;
	int		i;
	t_list	*list1;
	t_list	*list2;
	void	*tmp;

	if (!(begin_list))
		return ;
	count = ft_list_size2(begin_list);
	i = 0;
	while (i < count / 2)
	{
		list1 = ft_list_at2(begin_list, i);
		list2 = ft_list_at2(begin_list, count - 1 - i);
		tmp = list1->content;
		list1->content = list2->content;
		list2->content = tmp;
		i++;
	}
}
