/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_normal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/18 23:20:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** la focntion size_to mal permet de determiner la taille
** de la chaine de caracter
** et la malloc pour renvoyer str
*/

char		*size_to_mal(char *s, int *idx)
{
	int		j;
	int		e;
	char	*str;

	e = 0;
	j = 0;
	while ((s[*idx + j]) && ft_isspace(s[*idx + j]) == 0 && e == 0)
	{
		if (s[*idx + j] == '\\')
			j += 1;
		if (s[*idx + j] == '$' && (s[*idx + j + 1] != '\\'))
			e = 1;
		else if (ft_strchr_int("|;><", s[*idx + j]) == 1)
			e = 1;
		else
			j++;
	}
	j++;
	if (!(str = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	str = ft_memset(str, '\0', j + 1);
	return (str);
}

/*
** env_finder permet de trouver le nom de la variable qu'on cherche
** pour ensuite aller la chercher avec la fonciton getenv
*/

char		*env_finder(char *s, int *i, t_shell *glob)
{
	int		h;
	char	*str;
	char	*s1;

	h = 0;
	h++;
	if (ft_isalpha(s[*i + h]) != 1)
	{
		*i += 2;
		return ft_strdup("");
	}
	while (s[*i + h] != '\0' && (ft_isalnum(s[*i + h]) == 1  || s[*i + h] == '_'))
		h++;
	if (!(str = malloc(sizeof(char) * (h + 1))))
		return (NULL);
	
	glob->lex->e = h;
	h = 0;
	*i = *i+1;
	//h++;
	while (s[*i + h] != '\0' && (ft_isalnum(s[*i + h]) == 1  || s[*i + h] == '_'))
	{
		str[h] = s[*i + h];
		h++;
	}
	str[h] = '\0';
	//ft_putstr(str);
	s1 = ft_getenv(glob->list_env, str);
	free(str);
	*i = *i-1;
	return (s1);
}

/*
** manage_normal permet de recuper la chaine de caractere
** tout en gerant les exceptions
** doit etre reduite pour passer la norme si ce n'est pas fait
*/

char		*manage_normal(char *s, int *idx, t_shell *glob, char *str)
{
	char	c;
	int		j;

	c = '\0';
	while ((c = s[*idx]) && ft_isspace(s[*idx]) == 0 &&
	c != '\'' && c != '\"')
	{
		glob->lex->j = j;
		if (c == '\\')
			*idx += 1;
		if (c == '$' && (s[*idx + 1] != '\\'))
			return (join_env(idx, s, glob, str));
		else if (ft_strchr_int("|;><", s[*idx]) == 1)
			return (str);
		else
			str = manage_end(str, idx, s, &j);
	}
	return (str);
}