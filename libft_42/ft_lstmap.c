/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 01:41:25 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 23:22:35 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Itère sur la liste lst et applique la fonction f au contenu de chaque élément
** Crée une nouvelle liste résultant des applications successives de f. la
** fonction del est la pour detruire le contenu d un element si necessaire
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		if (!(temp = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&new, *del);
			return (NULL);
		}
		ft_lstadd_back(&new, temp);
		lst = lst->next;
	}
	return (new);
}
