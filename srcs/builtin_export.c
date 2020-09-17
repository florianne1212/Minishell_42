/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:09:34 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/09/02 11:15:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** la fonction print_value permet d'afficher
** les backslash comme dans export dans bash
*/

void			print_value(char *str, int fd)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\\')
			ft_putchar_fd('\\', fd);
		ft_putchar_fd(str[i], fd);
		i++;
	}
}

/*
** -----------builtin export-----------
** cree nouvelles variables d'environnement
** doivent etre presentees sous la forme
** name = value
*/

int				ft_putenv_null(t_list_env **export, char *string)
{
	char		*name;
	int			ret;

	if (!(name = find_name(string)))
		return (errno_return_int(ENOMEM, 1));
	ret = ft_setenv(export, name, NULL, 1);
	free(name);
	return (ret);
}

int				ft_putenv_export(t_list_env **env, char *string)
{
	char		*name;
	char		*value;
	int			ret;

	if (!string || !ft_isinstring('=', string))
		return (errno_return_int(EINVAL, -1));
	if (!(name = find_name(string)))
		return (errno_return_int(ENOMEM, -1));
	if (!(value = find_value(string)))
		return (errno_return_int(ENOMEM, -1));
	ret = ft_setenv(env, name, value, 1);
	free(name);
	free(value);
	return (ret);
}

void			builtin_export_message(char *str)
{
	ft_putstr_fd("minishell: export : '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': ", 2);
	ft_putendl_fd(strerror(errno), 2);
}

int				builtin_export(t_shell *glob, int fd, char **arg)
{
	int			i;
	int			ret;
	int			a;

	ret = 0;
	a = 0;
	if (ft_strlen_array((void **)arg) == 1)
		env_sorted(glob, fd);
	i = 1;
	while (arg[i])
	{
		if ((a = check_argi(arg[i])) == 2)
			ret = ft_putenv_append(&glob->list_env, arg[i]);
		else if (a == 0)
			return (1);
		else if (ft_isinstring('=', arg[i]) == 0)
			ret = ft_putenv_null(&glob->list_env, arg[i]);
		else if ((ft_putenv_export(&glob->list_env, arg[i]) == -1))
		{
			builtin_export_message(arg[i]);
			ret = 1;
		}
		i++;
	}
	return (ret);
}
