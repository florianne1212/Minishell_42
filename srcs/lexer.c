/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/19 21:50:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			nbr_words(char const *s, t_shell *glob)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	while (s[i] != '\0')
	{
		while (ft_isspace(s[i]) == 1 && s[i] != '\0')
			i++;
		while (ft_strchr_int("<>|;", s[i]) == 1 && s[i] != '\0')
		{
			a++;
			i++;
		}
		if (ft_strchr_int("<>|;", s[i]) == 0 && ft_isspace(s[i]) == 0)
		{
			a++;
			while (ft_strchr_int("<>|;", s[i]) == 0 &&
			ft_isspace(s[i]) == 0 && s[i] != '\0')
				i++;
		}
	}
	(void)glob;
	return (a);
}

void		init_lex(t_shell *glob, char *line)
{
	int		i;

	i = 0;
	if (!(glob->lex = malloc(sizeof(t_lex))))
		return ;
	glob->lex->nb_words = 0;
	glob->lex->tokens = NULL;
	glob->lex->count = 0;
	glob->lex->i = 0;
	glob->lex->j = 0;
	glob->lex->e = 0;
	glob->lex->nb_words = nbr_words(line, glob);
	if (!(glob->lex->tokens = (t_token **)malloc(sizeof(t_token *) *
	(glob->lex->nb_words + 1))))
		return ;
	while (i <= glob->lex->nb_words)
	{
		glob->lex->tokens[i] = NULL;
		i++;
	}
}

void		clean_lexer(t_shell *glob)
{
	int e;
	int index;

	index = 1;
	e = glob->lex->count;
	while (index <= e)
	{
		if (glob->lex->tokens[index]->type == TT_STRING)
			free(glob->lex->tokens[index]->str);
		index++;
	}
	index = 0;
	while (index <= glob->lex->nb_words)
	{
		free(glob->lex->tokens[index]);
		glob->lex->tokens[index] = NULL;
		index++;
	}
	free(glob->lex->tokens);
	free(glob->lex);
}

int			lexe_line(char *line, t_shell *glob)
{
	int		index;

	index = 0;
	init_lex(glob, line);
	while (index < (int)ft_strlen(line))
	{
		if (line[index] == '|')
			put_pipe(&index, line, glob);
		else if (line[index] == ';')
			put_semicolon(&index, line, glob);
		else if (line[index] == '<')
			put_input(&index, line, glob);
		else if (line[index] == '>')
		{
			if (line[index + 1] == '>')
				put_append(&index, line, glob);
			else
				put_output(&index, line, glob);
		}
		else
			put_string(&index, line, glob);
		index++;
	}
	parser(glob, 1);
	clean_lexer(glob);
	return (1);
}
