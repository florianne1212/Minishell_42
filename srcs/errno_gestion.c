/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 12:23:08 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/23 08:52:00 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** --------errno return str----------
** set errno and return the secund arg as string
*/

char		*errno_return_str(int errnocode, char *return_value)
{
	errno = errnocode;
	return (return_value);
}

/*
** --------errno return int----------
** set errno and return the secund arg as int
*/

int			errno_return_int(int errnocode, int return_value)
{
	errno = errnocode;
	return (return_value);
}

/*
** -----------split destructor-----------
** destroy an allocated string array
*/

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

/*
** --------destroy split errno return str----------
** destroy string array
** set errno and return the third arg as str
*/

char		*destroy_split_errno_ret_str(char **split, int errnocode, char *ret)
{
	split_destructor(split);
	return (errno_return_str(errnocode, ret));
}
