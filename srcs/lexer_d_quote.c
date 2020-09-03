/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/18 13:41:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** join_env permet de faire un strjoin de :
** 	- la variable d'environnement
** 	- ou la valeur de retour (si $? est envoye)
** (si il n'y a pas de backslash avant)
** avec str elle est utilise pour les chaine entre guillemets
** ou les chaines simples
** j esst egale a la ou on en est dans la chaine str j'ai
** du la passer dans la structure car sinon ca passait pas la norme
*/

char		*join_env(int *idx, char *s, t_shell *glob, char *str)
{
	char	*s2;
	char	*tmp;
	int		j;

	j = glob->lex->j;
	if (s[*idx] == '$' && s[*idx + 1] == '?')
	{
		s2 = ft_itoa(global_retour);
		*idx += 2;
	}
	else
	{
		s2 = env_finder(s, idx, glob);
		*idx += glob->lex->e;
	}
	if (s2 != NULL)
	{
		tmp = str;
		str = ft_strjoin(tmp, s2);
		free(tmp);
		free(s2);
	}
	return (str);
}

char		*manage_end(char *str, int *idx, char *s, int *j)
{
	char *tmp;

	tmp = str;
	str = add_to_1d(tmp, s[*idx]);
	*j += 1;
	*idx += 1;
	return (str);
}

/*
** manage_d_quote permet de recuper la chaine entre guillemets
** ou commencant par un guillemet tout en gerant les exceptions
** doit etre reduite pour passer la norme si ce n'est pas fait
*/

char		*manage_d_quote(char *s, int *idx, t_shell *glob, char *str)
{
	char	c;
	int		j;

	c = '\0';
	*idx = *idx + 1;
	while ((c = s[*idx]))
	{
		glob->lex->j = j;
		if (c == '\\' && ft_strchr("$\\\"", s[*idx + 1]) != 0)
			*idx += 1;
		if (c == '$' && (s[*idx - 1] != '\\'))
			str = join_env(idx, s, glob, str);
		else if (c == '"' && (s[*idx - 1] != '\\'))
		{
			*idx = *idx + 1;
			return (str);
		}
		else
			str = manage_end(str, idx, s, &j);
	}
	return (str);
}
