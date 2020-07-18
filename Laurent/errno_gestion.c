/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 12:23:08 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/19 00:34:04 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*errno_return_str(int errnocode, char *return_value)
{
	errno = errnocode;
	return (return_value);
}

int			errno_return_int(int errnocode, int return_value)
{
	errno = errnocode;
	return (return_value);
}

void		split_destructor(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}

char		*destroy_split_errno_ret_str(char **split, int errnocode, char *ret)
{
	split_destructor(split);
	return (errno_return_str(errnocode, ret));
}
