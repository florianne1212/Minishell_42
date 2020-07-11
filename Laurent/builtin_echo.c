/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 17:28:13 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/11 18:09:42 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_shell *glob, int fd, char **arg)
{
	int		i;
	int		n_opt;
	t_shell	*for_nothing;

	i = 1;
	n_opt = 0;
	if (!(ft_strcmp(arg[1], "-n")))
	{
		n_opt = 1;
		i++;
	}
	while (arg[i])
	{
		ft_putstr_fd(arg[i], fd);
		if (arg[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (!n_opt)
		ft_putchar_fd('\n', fd);
	for_nothing = glob;
	return (0);
}
