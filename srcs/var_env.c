/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <fcoudert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/06/25 22:05:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**fonction qui permet de trouver le nom de la variable
*/

char			*find_name(char *str)
{
	int			i;
	char		*name;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	if (!(name = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

/*
**fonction qui permet de trouver la valeur de la variable
*/

char			*find_value(char *str)
{
	int			i;
	int			j;
	char		*value;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	i++;
	while (str[i + j] != '\0')
		j++;
	if (!(value = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	j = i;
	i = 0;
	while (str[j] != '\0')
	{
		value[i] = str[j];
		i++;
		j++;
	}
	value[i] = '\0';
	return (value);
}

/*
**fonction qui met les variables d'environnement dans liste chainee
**en complement de sort envp
*/

t_list_env		*add_link(t_list_env *list, char *str)
{
	t_list_env	*tmp;

	if (!(tmp = malloc(sizeof(t_list_env))))
		return (NULL);
	if (tmp)
	{
		tmp->name = find_name(str);
		tmp->value = find_value(str);
		tmp->next = list;
	}
	return (tmp);
}

/*
** fonction qui affiche la liste chainee
*/

void			print_list(t_list_env *list)
{
	while (list != NULL)
	{
		ft_putstr("\n name = ");
		ft_putstr(list->name);
		ft_putstr("\n value = ");
		ft_putstr(list->value);
		list = list->next;
	}
}

/*
**fonction qui met les variables d'environnement dans liste chainee
**en complement de add link
*/

void			sort_envp(char **envp, t_shell *glob)
{
	int			i;

	i = 0;
	glob->list_env = NULL;
	while (envp[i])
	{
		glob->list_env = add_link(glob->list_env, envp[i]);
		i++;
	}
}
