/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <fcoudert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/09/10 12:20:35 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				check_shlvl(char *value)
{
	int			r;
	int			j;

	j = 0;
	r = 0;
	while (value[j] != '\0')
	{
		if (ft_isdigit(value[j]) == 0 && j != 0)
			r = 1;
		j++;
	}
	return (r);
}

void			manage_shlvl(t_shell *glob)
{
	char		*value;
	char		*test;
	int			i;

	value = ft_getenv(glob->list_env, "SHLVL");
	if (check_shlvl(value) == 1)
		i = 0;
	else
		i = ft_atoi(value);
	if (i >= 0)
		i++;
	if (i < 0)
		i = 0;
	test = ft_itoa(i);
	ft_setenv(&glob->list_env, "SHLVL", test, 1);
	free(test);
	free(value);
}
