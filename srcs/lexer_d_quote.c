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
** la focntion size_to malloc permet de determiner la taille
** de la chaine de caracter entre guillemets
** et la malloc pour renvoyer str
*/

char		*size_to_malloc(char *s, int *i)
{
	int		j;
	int		e;
	char	*str;

	e = 0;
	j = 0;
	while ((s[*i + j]) && e == 0)
	{
		if (s[*i + j] == '\\' && ft_strchr("$\\\"", s[*i + j + 1]) != 0)
			j += 1;
		if (s[*i + j] == '$' && (s[*i + j - 1] != '\\'))
			e = 1;
		else if (s[*i + j] == '"' && (s[*i + j - 1] != '\\'))
			e = 1;
		else
			j++;
	}
	if (!(str = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	str = ft_memset(str, '\0', j + 1);
	return (str);
}

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
		s2 = env_finder(s, (*idx), glob);
		*idx += glob->lex->e;
	}
	if (s2 != NULL)
	{
		str[j] = '\0';
		tmp = str;
		str = ft_strjoin(tmp, s2);
		free(tmp);
		free(s2);
	}
	return (str);
}

char		*manage_end(char *str, int *idx, char *s, int *j)
{
	str[*j] = s[*idx];
	*j += 1;
	*idx += 1;
	return (str);
}

/*
** manage_d_quote permet de recuper la chaine entre guillemets
** ou commencant par un guillemet tout en gerant les exceptions
** doit etre reduite pour passer la norme si ce n'est pas fait
*/

char		*manage_d_quote(char *s, int *idx, t_shell *glob)
{
	char	c;
	char	*str;
	int		j;

	c = '\0';
	str = size_to_malloc(s, idx);
	j = 0;
	while ((c = s[*idx]))
	{
		glob->lex->j = j;
		if (c == '\\' && ft_strchr("$\\\"", s[*idx + 1]) != 0)
			*idx += 1;
		if (c == '$' && (s[*idx - 1] != '\\'))
			return (join_env(idx, s, glob, str));
		else if (c == '"' && (s[*idx - 1] != '\\'))
		{
			str[j] = '\0';
			return (str);
		}
		else
			str = manage_end(str, idx, s, &j);
	}
	str[j] = '\0';
	return (str);
}

/*
** la fonction put_d_quote permet d'ajouter
** un token dans le tableau de structure
** et de mettre d'assigner TT_STRING au type
** ainsi que de d'assigner la chaine de caractere
** a str
*/

void		put_d_quote(int *idx, char *s, t_shell *glob, char c)
{
	int		j;
	t_token	*ttok;

	j = 0;
	if (s[*idx] != '\0' && s[*idx] == c)
	{
		*idx += 1;
		if (!(ttok = malloc(sizeof(t_token))))
			return ;
		ttok->type = TT_STRING;
		ttok->str = manage_d_quote(s, idx, glob);
		glob->lex->tokens[glob->lex->count] = ttok;
		glob->lex->count++;
		fflush(stdout);
		*idx += 1;
	}
}
