/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <fcoudert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/06/25 22:05:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		put_pipe(int *index, char *s, t_shell *glob)
{
	t_token	*ttok;

	if (s[*index] == '|' && s[*index] != '\0')
	{
		if (!(ttok = malloc(sizeof(t_token))))
			return ;
		ttok->type = TT_PIPE;
		ttok->str = "pipe";
		glob->lex->count++;
		glob->lex->tokens[glob->lex->count] = ttok;
		printf(".%s.", glob->lex->tokens[glob->lex->count]->str);
		fflush(stdout);
	}
}

void		put_input(int *index, char *s, t_shell *glob)
{
	t_token	*ttok;

	if (s[*index] == '<' && s[*index] != '\0')
	{
		if (!(ttok = malloc(sizeof(t_token))))
			return ;
		ttok->type = TT_IN;
		ttok->str = "input";
		glob->lex->count++;
		glob->lex->tokens[glob->lex->count] = ttok;
		printf(".%s.", glob->lex->tokens[glob->lex->count]->str);
		fflush(stdout);
	}
}

void		put_output(int *index, char *s, t_shell *glob)
{
	t_token	*ttok;

	if (s[*index] == '>' && s[*index] != '\0')
	{
		if (!(ttok = malloc(sizeof(t_token))))
			return ;
		ttok->type = TT_OUT;
		ttok->str = "output";
		glob->lex->count++;
		glob->lex->tokens[glob->lex->count] = ttok;
		printf(".%s.", glob->lex->tokens[glob->lex->count]->str);
		fflush(stdout);
		index++;
	}
}

void		put_semicolon(int *index, char *s, t_shell *glob)
{
	t_token	*ttok;

	if (s[*index] == ';' && s[*index] != '\0')
	{
		if (!(ttok = malloc(sizeof(t_token))))
			return ;
		ttok->type = TT_SEMICOLOM;
		ttok->str = "semicolon";
		glob->lex->count++;
		glob->lex->tokens[glob->lex->count] = ttok;
		printf(".%s.", glob->lex->tokens[glob->lex->count]->str);
		fflush(stdout);
	}
}

int		put_string(int index, char *s, t_shell *glob)
{
	int		j;
	t_token	*ttok;

	j = 0;
	while (ft_isspace(s[index]) == 1 && s[index] != '\0')
		index++;
	if (ft_isalpha(s[index]) == 1  && s[index] != '\0')
	{
		if (!(ttok = malloc(sizeof(t_token))))
			return 0;
		ttok->type = TT_STRING;
		ttok->str = "string";
		while (ft_isalpha(s[index + j]) == 1 && s[index + j] != '\0')
		{
			//ttok->str[j] = s[i];
			//index++;
			j++;
			//j++;
		}
		glob->lex->count++;
		glob->lex->tokens[glob->lex->count] = ttok;
		printf(".%s.", glob->lex->tokens[glob->lex->count]->str);
		fflush(stdout);
		while (ft_isspace(s[index + j]) == 1 && s[index + j] != '\0')
			j++;
		return(j - 1);
	}
	return (0);
}

