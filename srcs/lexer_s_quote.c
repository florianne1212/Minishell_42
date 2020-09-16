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

char		*manage_quote(char *s, int *idx, char *str)
{
	char	*tmp;

	*idx = *idx + 1;
	while (s[*idx] != '\0' && s[*idx] != '\'')
	{
		tmp = str;
		str = add_to_1d(tmp, s[*idx]);
		*idx += 1;
	}
	*idx = *idx + 1;
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
** la fonction put_string permet de renvoyer
** a la fonction qui va gerer correctement si la chaine
** de caractere est entre single quote, entre double quote ou sans rien
*/

void		put_string(int *idx, char *s, t_shell *glob)
{
	t_token	*ttok;

	if (!(ttok = malloc(sizeof(t_token))))
		return ;
	ttok->type = TT_STRING;
	ttok->str = ft_strdup("");
	while (ft_isspace(s[*idx]) == 1)
		*idx += 1;
	while (1)
	{
		if (s[*idx] == '\'')
			ttok->str = manage_quote(s, idx, ttok->str);
		else if (s[*idx] == '\"')
			ttok->str = manage_d_quote(s, idx, glob, ttok->str);
		else
			ttok->str = manage_normal(s, idx, glob, ttok->str);
		if (ft_isspace(s[*idx]) == 1 || s[*idx] == '\0' ||
		ft_strchr_int("|;><", s[*idx]) == 1)
			break ;
	}
	add_to_2d((void***)&glob->lex->tokens, ttok);
	glob->lex->count++;
}

void		**add_to_2d(void ***of, void *ptr)
{
	size_t	length;
	size_t	size;
	void	**nw;

	length = ft_strlen_array(*of);
	size = sizeof(void*) * (length + 1 + 1);
	if (!(nw = malloc(size)))
		return (NULL);
	if (*of)
		ft_memcpy(nw, *of, size - sizeof(void*));
	nw[length] = ptr;
	nw[length + 1] = NULL;
	free(*of);
	return (*of = nw);
}

char		*add_to_1d(char *of, char ptr)
{
	size_t	length;
	size_t	size;
	char	*nw;

	length = ft_strlen(of);
	size = sizeof(char) * (length + 1 + 1);
	if (!(nw = malloc(size)))
		return (NULL);
	ft_memcpy(nw, of, size - sizeof(char));
	nw[length] = ptr;
	nw[length + 1] = '\0';
	free(of);
	return (nw);
}
