/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/19 22:15:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** strlen_array permet de connaitre la "hauteur"
** de notr char **
*/

int			ft_strlen_array(char **s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
** add_to_array permet d'ajouter un char * a la suite
** d'un char **;
*/

char		**add_to_array(char **s1, char *s2)
{
	int		ss1;
	int		i;
	char	**ss3;

	i = 0;
	ss3 = NULL;
	if (s1)
	{
		ss1 = ft_strlen_array(s1);
		if (!(ss3 = (char **)malloc(sizeof(char *) * (ss1 + 2))))
			return (NULL);
		while (s1[i])
		{
			ss3[i] = s1[i];
			i++;
		}
		free(s1);
		ss3[i++] = ft_strdup(s2);
		ss3[i] = NULL;
	}
	return (ss3);
}

char		**add_front_to_array(char **s1, char *s2)
{
	int		ss1;
	int		i;
	int 	j;
	char	**ss3;

	i = 0;
	j = 0;
	ss3 = NULL;
	if (s1)
	{
		ss1 = ft_strlen_array(s1);
		if (!(ss3 = (char **)malloc(sizeof(char *) * (ss1 + 2))))
			return (NULL);
		ss3[i] = s2;
		i++;
		while (s1[j])
		{
			ss3[i] = s1[j];
			i++;
			j++;
		}
		//free(s1);
		ss3[i] = NULL;
	}
	return (ss3);
}