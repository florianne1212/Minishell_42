/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 22:09:34 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/22 22:00:59 by lcoiffie         ###   ########.fr       */
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
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(list->value, fd);
		ft_putstr_fd("\"\n", fd);
		list = list->next;
	}
}

/*
** -----------builtin export-----------
** cree nouvelles variables d'environnement
** doivent etre presentees sous la forme
** name = value
*/

int			builtin_export(t_shell *glob, int fd, char **arg)
{
	int	i;
	int ret;

	ret = 0;
	if (!arg[1])
		env_sorted(glob, fd);
	i = 1;
	while (arg[i])
	{
		if ((ft_putenv(&glob->list_env, arg[i]) == -1))
		{
			ft_putstr_fd("bash: export : `", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putstr_fd("': ", 2);
			ft_putendl_fd(strerror(errno), 2);
			ret = 1;
		}
		i++;
	}
	return (ret);
}
