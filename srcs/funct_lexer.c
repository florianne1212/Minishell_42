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

/*
** la fonction put_pipe permet d'ajouter
** un token dans le tableau de structure
** et de mettre d'assigner TT_PIPE au type
*/

void			put_pipe(int *index, char *s, t_shell *glob)
{
	t_token		*ttok;

	if (s[*index] == '|' && s[*index] != '\0')
	{
		if (!(ttok = malloc(sizeof(t_token))))
			return ;
		ttok->type = TT_PIPE;
		ttok->str = "pipe";
		glob->lex->tokens[glob->lex->count] = ttok;
		printf(".%s.", glob->lex->tokens[glob->lex->count]->str);
		glob->lex->count++;
		fflush(stdout);
	}
}

/*
** la fonction put_input permet d'ajouter
** un token dans le tableau de structure
** et de mettre d'assigner TT_IN au type
*/

void			put_input(int *index, char *s, t_shell *glob)
{
	t_token		*ttok;

	if (s[*index] == '<' && s[*index] != '\0')
	{
		if (!(ttok = malloc(sizeof(t_token))))
			return ;
		ttok->type = TT_IN;
		ttok->str = "input";
		glob->lex->tokens[glob->lex->count] = ttok;
		printf(".%s.", glob->lex->tokens[glob->lex->count]->str);
		glob->lex->count++;
		fflush(stdout);
	}
}

/*
** la fonction put_output permet d'ajouter
** un token dans le tableau de structure
** et de mettre d'assigner TT_OUT au type
*/

void			put_output(int *index, char *s, t_shell *glob)
{
	t_token		*ttok;

	if (s[*index] == '>' && s[*index] != '\0')
	{
		if (!(ttok = malloc(sizeof(t_token))))
			return ;
		ttok->type = TT_OUT;
		ttok->str = "output";
		glob->lex->tokens[glob->lex->count] = ttok;
		printf(".%s.", glob->lex->tokens[glob->lex->count]->str);
		glob->lex->count++;
		fflush(stdout);
		index++;
	}
}

/*
** la fonction put_semicolon permet d'ajouter
** un token dans le tableau de structure
** et de mettre d'assigner TT_SEMICOLON au type
*/

void			put_semicolon(int *index, char *s, t_shell *glob)
{
	t_token		*ttok;

	if (s[*index] == ';' && s[*index] != '\0')
	{
		if (!(ttok = malloc(sizeof(t_token))))
			return ;
		ttok->type = TT_SEMICOLOM;
		ttok->str = "semicolon";
		glob->lex->tokens[glob->lex->count] = ttok;
		printf(".%s.", glob->lex->tokens[glob->lex->count]->str);
		glob->lex->count++;
		fflush(stdout);
	}
}

/*
** la fonction put_append permet d'ajouter
** un token dans le tableau de structure
** et de mettre d'assigner TT_APPEND au type
*/

void			put_append(int *index, char *s, t_shell *glob)
{
	t_token		*ttok;

	if (s[*index] == '>' && s[*index + 1] == '>' && s[*index] != '\0')
	{
		if (!(ttok = malloc(sizeof(t_token))))
			return ;
		ttok->type = TT_APPEND;
		ttok->str = "append";
		glob->lex->tokens[glob->lex->count] = ttok;
		printf(".%s.", glob->lex->tokens[glob->lex->count]->str);
		glob->lex->count++;
		fflush(stdout);
		*index += 1;
	}
}
