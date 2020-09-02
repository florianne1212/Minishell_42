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
**-----------ft swap------------
** echange 2 strings
*/

static void	ft_swap(char **s1, char **s2)
{
	char *temp;

	temp = *s2;
	*s2 = *s1;
	*s1 = temp;
}

/*
**---------ft list sort env---------
** permet d'ordonner liste chainee dans ordre alphabetiaue
*/

static void	ft_list_sort_env(t_list_env **begin_list, int (*cmp)())
{
	t_list_env	*list1;
	t_list_env	*list2;

	if (!(*begin_list) || !((*begin_list)->next))
		return ;
	list1 = *begin_list;
	while (list1 && list1->next)
	{
		list2 = list1->next;
		while (list2)
		{
			if (((*cmp)(list1->name, list2->name)) > 0)
			{
				ft_swap(&list1->name, &list2->name);
				ft_swap(&list1->value, &list2->value);
			}
			list2 = list2->next;
		}
		list1 = list1->next;
	}
}

/*
** la fonction print_value permet d'afficher
** les backslash comme dans export dans bash
*/

void		print_value(char *str, int fd)
{
	int i;

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
** --------env sorted -----------
** lorsque export utilise sans argument
** fait "env" avec liste triee
*/

static void	env_sorted(t_shell *glob, int fd)
{
	t_list_env *list;

	list = glob->list_env;
	ft_list_sort_env(&list, ft_strcmp);
	while (list != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(list->name, fd);
		if(list->value != NULL)
		{
			ft_putstr_fd("=\"", fd);
			print_value(list->value, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
		list = list->next;
	}
}

/*
** -----------builtin export-----------
** cree nouvelles variables d'environnement
** doivent etre presentees sous la forme
** name = value
*/

// int			builtin_export(t_shell *glob, int fd, char **arg)
// {
// 	int	i;
// 	int ret;

// 	ret = 0;
// 	if (!arg[1])
// 		env_sorted(glob, fd);
// 	i = 1;
// 	while (arg[i])
// 	{
// 		if ((ft_putenv(&glob->list_env, arg[i]) == -1))
// 		{
// 			ft_putstr_fd("bash: export : `", 2);
// 			ft_putstr_fd(arg[i], 2);
// 			ft_putstr_fd("': ", 2);
// 			ft_putendl_fd(strerror(errno), 2);
// 			ret = 1;
// 		}
// 		i++;
// 	}
// 	return (ret);
// }

int			ft_putenv_null(t_list_env **export, char *string)
{
	char	*name;
	int		ret;

	if (!(name = find_name(string)))
		return (errno_return_int(ENOMEM, -1));
	ret = ft_setenv(export, name, NULL, 1);
	free(name);
	//free(value);
	return (ret);
}

int			ft_putenv_export(t_list_env **env, char *string)
{
	char	*name;
	char	*value;
	int		ret;

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
	while (str[i] != '\0' &&  (str[i + 1] != '=' && str[i] != '+'))
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}


int			ft_putenv_append(t_list_env **env, char *string)
{
	char	*name;
	char	*value;
	//char	*append;
	//char	*tmp;
	int		ret;
	int		i;

	i = 0;
	if (!(name = find_name_bis(string)))
		return (errno_return_int(ENOMEM, -1));
	if (!(value = find_value(string)))
			return (errno_return_int(ENOMEM, -1));
	ret = ft_setenv(env, name, value, 2);
	free(name);
	free(value);
	//free(append);
	return (ret);
}

int			check_argi(char *str)
{
	int i;
	char c;

	i = 0;
	if (ft_isdigit(str[0]) == 1)
	{
		ft_putstr_fd("\nbash: export: ", 2);
		ft_putstr_fd(str,2);
		ft_putstr_fd(" not a valid identifier \n", 2);
		return(0);
	}
	while ((c = str[i]) != '\0')
	{
		if (c == '=' || (c == '+' && str[i + 1] == '='))
 			break ;
		//ft_putchar_fd(str[i], 2); 
		if (ft_isalnum(str[i]) == 0)
		{
			ft_putstr_fd("\nbash: export: ", 2);
			ft_putstr_fd(str,2);
			ft_putstr_fd(" not a valid identifier \n", 2);
			return(0);
		}
		
		i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i + 1] == '=' && str[i] == '+')
			return(2);
		i++;
	}
	return(1);	
}

int			builtin_export(t_shell *glob, int fd, char **arg)
{
	int	i;
	int ret;

	ret = 0;

	if (ft_strlen_array((void **)arg) == 1)
		env_sorted(glob, fd);
	i = 1;
	while (arg[i])
	{
		if(check_argi(arg[i]) == 2)
			ft_putenv_append(&glob->list_env, arg[i]);
		else if (ft_isinstring('=', arg[i]) == 0)
			ft_putenv_null(&glob->list_env, arg[i]);
		else if ((ft_putenv_export(&glob->list_env, arg[i]) == -1))
		{
			ft_putstr_fd("bash: export : '", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putstr_fd("': ", 2);
			ft_putendl_fd(strerror(errno), 2);
			ret = 1;
		}
		i++;
	}
	return(1);
}