/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 17:28:13 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/08/21 08:46:54 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** --------------is_a_n_opt---------------
** verifie si option -n
*/

int	is_a_n_opt(char *arg, int *opt)
{
	int	j;

	j = 0;
	if (arg[0] != '-')
		return (0);
	j++;
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (0);
		j++;
	}
	*opt = 1;
	return (1);
}

/*
**--------builtin echo ------------
** echo +/- option -n
*/

int	builtin_echo(t_shell *glob, int fd, char **arg)
{
	int		i;
	int		n_opt;

	i = 1;
	n_opt = 0;
	while (arg[i] && is_a_n_opt(arg[i], &n_opt))
		i++;
	while (arg[i])
	{
		ft_putstr_fd(arg[i], fd);
		if (arg[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (!n_opt)
		ft_putchar_fd('\n', fd);
	(void)glob;
	return (0);
}
