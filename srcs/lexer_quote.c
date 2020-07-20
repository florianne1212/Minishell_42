/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <fcoudert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/06/25 22:05:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*manage_quote(char *s, int i, char c)
{
	int		j;
	char	*str;

	j = 0;
	while (s[i + j] != '\0' && s[i + j] != c)
		j++;
	if (s[i + j] == '\0')
		ft_putstr("\nmissing end of quote");
	if (!(str = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	j = 0;
	while (s[i + j] != '\0' && s[i + j] != c)
	{
		str[j] = s[i + j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

int			put_quote(int i, char *s, t_shell *glob, char c)
{
	int		j;
	t_token	*ttok;

	j = 0;
	if (s[i + j] != '\0' && s[i + j] == c)
	{
		j++;
		if (!(ttok = malloc(sizeof(t_token))))
			return (0);
		ttok->type = TT_STRING;
		ttok->str = manage_quote(s, i + j, c);
		while (s[i + j] != '\0' && s[i + j] != c)
			j++;
		glob->lex->count++;
		glob->lex->tokens[glob->lex->count] = ttok;
		printf(".%s.", glob->lex->tokens[glob->lex->count]->str);
		fflush(stdout);
		return (j);
	}
	return (0);
}

int			put_string(int i, char *s, t_shell *glob)
{
	int		j;

	j = 0;
	while (ft_isspace(s[i + j]) == 1 && s[i + j] != '\0')
		j++;
	if (s[i + j] == '\'')
		j += put_quote((i + j), s, glob, '\'');
	else if (s[i + j] == '\"')
		j += put_quotation((i + j), s, glob, '\"');
	else 
		j += put_normal((i + j), s, glob);
	return (j);
}
