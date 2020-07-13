/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_strs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 12:29:43 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/06/05 21:51:05 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Crée une nouvelle liste en y mettant les chaines de caracteres pointées par
** les éléments tableau strs • size est la taille de strs
*/

#include "libft.h"

t_list	*ft_list_push_strs(int size, char **strs)
{
	t_list	*new;
	int		i;

	new = NULL;
	i = 0;
	while (i < size)
	{
		ft_list_push_front(&new, strs[i]);
		i++;
	}
	return (new);
}
