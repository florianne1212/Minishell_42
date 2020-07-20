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

char		*manage_quote(char *s, int *idx, char c)
{
	char	*str;
	int j;

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

int			put_quote(int *idx, char *s, t_shell *glob, char c)
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
		glob->lex->count++;
		glob->lex->tokens[glob->lex->count] = ttok;
		printf(".%s.", glob->lex->tokens[glob->lex->count]->str);
		fflush(stdout);
		return (j);
	}
	return (0);
}

void			put_string(int *idx, char *s, t_shell *glob)
{
	int		j;

	j = 0;
	while (ft_isspace(s[*idx]) == 1 && s[*idx] != '\0')
		*idx+=1;
	if (s[*idx] == '\'')
		put_quote(idx, s, glob, '\'');
	else if (s[*idx] == '\"')
		put_quotation(idx, s, glob, '\"');
	else 
		put_normal((idx + j), s, glob);
	return ;
}
