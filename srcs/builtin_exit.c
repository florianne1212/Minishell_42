/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 18:13:59 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/13 10:18:35 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

long int	ft_atoi_long(const char *str)
{
	int			i;
	int			neg;
	long int	nbr;

	i = 0;
	neg = 1;
	nbr = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	return (nbr * neg);
}

int			check_atoilong(t_shell *glob, long int nbr, char **arg)
{
	long int		i;
	char			c;

	i = nbr % 10;
	if (i < 0)
		i = -i;
	c = arg[1][ft_strlen(arg[1]) - 1];
	if (((c - '0') != i) || ((nbr < 0) && (!(ft_isinstring('-', arg[1])))))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(arg[1], 2);
		ft_putstr_fd(": argument numerique necessaire\n", 2);
		glob->exit_code = 2;
		glob->running = 0;
		return (1);
	}
	return (0);
}

int			check_exit_arg(t_shell *glob, char **arg)
{
	int i;

	i = 0;
	if (arg[1][0] == '-' || arg[1][0] == '+')
		i++;
	while (arg[1][i])
	{
		if (arg[1][i] < '0' || arg[1][i] > '9')
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(arg[1], 2);
			ft_putstr_fd(": argument numerique necessaire\n", 2);
			glob->exit_code = 2;
			glob->running = 0;
			return (1);
		}
		i++;
	}
	if (arg[2])
	{
		ft_putstr_fd("exit: trop d'arguments\n", 2);
		return (1);
	}
	return (0);
}

int			builtin_exit(t_shell *glob, int fd, char **arg)
{
	long int	longlong;

	(void)fd;
	glob->exit_code = 0;
	if (arg[1])
	{
		if (check_exit_arg(glob, arg))
			return (1);
		if ((longlong = ft_atoi_long(arg[1])))
			if (check_atoilong(glob, longlong, arg))
				return (1);
		glob->exit_code = (unsigned char)longlong;
	}
	glob->running = 0;
	if (glob->exit_code == 0)
		glob->exit_code = glob->return_code;
	return (0);
}
