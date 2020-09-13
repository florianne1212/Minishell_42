/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 15:48:09 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/13 16:16:58 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**--------cd check args---------
**controle les arguments de cd dans un pipe
*/

static int	cd_check_args(char **arg)
{
	if (arg[1] && arg[2])
	{
		ft_putendl_fd("minishell: cd: trop d'arguments", 2);
		return (1);
	}
	if (!arg[1] || (!ft_strcmp(arg[1], "~")))
		return (0);
	else if (!(ft_strcmp(arg[1], "-")))
		return (0);
	else
		return (-1);
}

/*
**--------cd pipe---------
**renvoie erreurs  mais ne change pas de repertoire si cd est dans un pipe
*/

int			cd_pipe(char **arg)
{
	char	*absolute;
	char	*initial_dir;
	int		ret;

	if ((ret = cd_check_args(arg)) >= 0)
		return (ret);
	if (arg[1][0] == '/')
		absolute = ft_strdup(arg[1]);
	else
		absolute = change_rel_to_abs(arg[1]);
	initial_dir = getcwd(NULL, 0);
	if (chdir(absolute))
		return (cd_error(arg[1], 1, initial_dir, absolute));
	else
		chdir(initial_dir);
	if (initial_dir)
		free(initial_dir);
	if (absolute)
		free(absolute);
	return (0);
}
