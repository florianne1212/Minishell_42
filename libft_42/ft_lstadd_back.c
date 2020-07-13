/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:43:47 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 23:14:22 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Ajoute l’élément new à la fin de la liste
*/

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (!alst || !new)
		return ;
	if (*alst == NULL)
	{
		new->next = NULL;
		*alst = new;
	}
	else
	{
		new->next = NULL;
		ft_lstlast(*alst)->next = new;
	}
	return ;
}
