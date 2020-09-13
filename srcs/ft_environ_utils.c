/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environ_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 16:20:40 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/13 16:36:46 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isalnumunderscore(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) ||
			c == 95)
		return (1);
	return (0);
}

int	ft_isabashname(char *name)
{
	int i;

	if (!(ft_isalpha(name[0])) && (name[0] != 95))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!(ft_isalnumunderscore(name[i])))
			return (0);
		i++;
	}
	return (1);
}
