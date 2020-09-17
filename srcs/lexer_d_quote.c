/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_d_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/09/06 21:22:10 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char		*join_retour(int *idx, t_shell *glob)
{
	char	*s2;

	if (g_retour)
		s2 = ft_itoa(g_retour);
	else
	{
		s2 = ft_itoa(glob->return_code);
	}
	*idx += 2;
	return (s2);
}

char		*join_env(int *idx, char *s, t_shell *glob, char *str)
{
	char	*s2;
	char	*tmp;

	if (s[*idx] == '$' && s[*idx + 1] == '?')
		s2 = join_retour(idx, glob);
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

/*
** manage_d_quote permet de recuper la chaine entre guillemets
** ou commencant par un guillemet tout en gerant les exceptions
** doit etre reduite pour passer la norme si ce n'est pas fait
*/

char		*add_back(int i, char c, char *str, t_shell *glob)
{
	char	*tmp;

	if (i % 2 == 1 && c != '\0' && c != '$' && c != '\"')
	{
		tmp = str;
		str = add_to_1d(tmp, '\\');
	}
	glob->back = i % 2;
	return (str);
}

char		*do_back_double(char *s, int *idx, t_shell *glob, char *str)
{
	char	c;
	int		i;
	int		e;
	char	*tmp;

	e = 0;
	i = 0;
	glob->back = 0;
	if (s[*idx] == '\\')
	{
		while ((c = s[*idx]) && ft_isspace(s[*idx]) == 0 &&
		c != '\'' && c != '\"' && c == '\\')
		{
			i++;
			*idx += 1;
		}
		while (e < (i / 2))
		{
			tmp = str;
			str = add_to_1d(tmp, '\\');
			e++;
		}
	}
	str = add_back(i, s[*idx], str, glob);
	return (str);
}

char		*manage_d_quote(char *s, int *idx, t_shell *glob, char *str)
{
	char	c;
	int		j;

	c = '\0';
	*idx = *idx + 1;
	while ((c = s[*idx]))
	{
		glob->back = 0;
		glob->lex->j = j;
		if (c == '\\')
			str = do_back_double(s, idx, glob, str);
		if (s[*idx] == '$' && (s[*idx - 1] != '\\' || glob->back == 0) &&
		s[*idx + 1] != '\0' && ft_isspace(s[*idx + 1]) == 0)
			str = join_env(idx, s, glob, str);
		else if (s[*idx] == '"' && (s[*idx - 1] != '\\' || glob->back == 0))
		{
			*idx = *idx + 1;
			return (str);
		}
		else
			str = manage_end(str, idx, s, &j);
	}
	return (str);
}
