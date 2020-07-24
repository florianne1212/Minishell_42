/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_s_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/24 08:56:58 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** manage_quote renvoie la chaine de caractere qui est encadre
** par des quotes si la chaine a un quote de debut mais ne
** n'a pas de quote de fin on prend jusqu'a la fin
*/

char		*manage_quote(char *s, int *idx, char c)
{
	char	*str;
	int		j;

	j = 0;
	while (s[*idx + j] != '\0' && s[*idx + j] != c)
		j++;
	if (!(str = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	j = 0;
	while (s[*idx] != '\0' && s[*idx] != c)
	{
		str[j] = s[*idx];
		*idx += 1;
		j++;
	}
	str[j] = '\0';
	return (str);
}

/*
** la fonction put_s_quote permet d'ajouter
** un token dans le tableau de structure
** et de mettre d'assigner TT_STRING au type
** ainsi que de d'assigner la chaine de caractere
** a str
*/

int			put_s_quote(int *idx, char *s, t_shell *glob, char c)
{
	int		j;
	t_token	*ttok;

	j = 0;
	if (s[*idx] != '\0' && s[*idx] == c)
	{
		*idx += 1;
		if (!(ttok = malloc(sizeof(t_token))))
			return (0);
		ttok->type = TT_STRING;
		ttok->str = manage_quote(s, idx, c);
		glob->lex->tokens[glob->lex->count] = ttok;
		//printf("_.%s._", glob->lex->tokens[glob->lex->count]->str);
		glob->lex->count++;
		fflush(stdout);
		return (j);
	}
	return (0);
}

/*
** la fonction put_string permet de renvoyer
** a la fonction qui va gerer correctement si la chaine
** de caractere est entre single quote, entre double quote ou sans rien
*/

void		put_string(int *idx, char *s, t_shell *glob)
{
	int		j;

	j = 0;
	while (ft_isspace(s[*idx]) == 1 && s[*idx] != '\0')
		*idx += 1;
	if (s[*idx] == '\'')
		put_s_quote(idx, s, glob, '\'');
	else if (s[*idx] == '\"')
		put_d_quote(idx, s, glob, '\"');
	else
		put_normal((idx + j), s, glob);
	return ;
}
