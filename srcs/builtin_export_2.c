/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:09:34 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/02 11:15:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			*find_name_bis(char *str)
{
	int			i;
	char		*name;

	i = 0;
	while (str[i] != '\0' && (str[i + 1] != '=' && str[i] != '+'))
		i++;
	if (!(name = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] != '\0' && (str[i + 1] != '=' && str[i] != '+'))
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

int				ft_putenv_append(t_list_env **env, char *string)
{
	char		*name;
	char		*value;
	int			ret;

	if (!(name = find_name_bis(string)))
		return (errno_return_int(ENOMEM, -1));
	if (!(value = find_value(string)))
		return (errno_return_int(ENOMEM, -1));
	ret = ft_setenv(env, name, value, 2);
	free(name);
	free(value);
	return (ret);
}

int				check_argi_bis(char *str)
{
	int			i;
	char		c;

	i = 0;
	while ((c = str[i]) != '\0')
	{
		if (c == '=' || (c == '+' && str[i + 1] == '='))
			break ;
		if (c != '_' && ft_isalnum(str[i]) == 0)
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(" not a valid identifier \n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int				check_argi(char *str)
{
	int			i;

	i = 0;
	if (ft_isdigit(str[0]) == 1)
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" not a valid identifier \n", 2);
		return (0);
	}
	if (check_argi_bis(str) == 0)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i + 1] == '=' && str[i] == '+')
			return (2);
		i++;
	}
	return (1);
}
