/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 22:25:51 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 23:15:34 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Libère la mémoire de l’élément passé en argument en utilisant la fonction del
** puis avec free. La mémoire de next ne doit pas être free.
*/

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	(del)(lst->content);
	free(lst);
}
