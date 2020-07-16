/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <fcoudert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/06/25 22:05:40 by user42           ###   ########.fr       */
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

// void	destruct_lex(t_shell *glob)
// {
// 	/*while (i < glob->lex->nb_words)
// 	{
// 		if (glob->lex->tokens[i] != NULL)
// 		{
// 			free(glob->lex->tokens[i]);
// 			glob->lex->tokens[i] = NULL;
// 		}
// 		i++;
// 	}
// 	free(glob->lex);
// 	glob->lex = NULL;*/
// }

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
	glob->lex->nb_words = nbr_words(line, glob);
	if (!(glob->lex->tokens = (t_token **)malloc(sizeof(t_token *) *
	(glob->lex->nb_words + 1))))
		return ;
	while (i <= glob->lex->nb_words)
	{
		glob->lex->tokens[i] = (t_token *)malloc((sizeof(t_token)));
		i++;
	}
}

int			lexe_line(char *line, t_shell *glob)
{
	int		index;

	index = 0;
	init_lex(glob, line);
	while (line[index] != '\0')
	{
		//if (line[index] == (char)134)
		//	index += put_string(index, line, glob);
		if (line[index] == '|')
			put_pipe(&index, line, glob);
		else if (line[index] == ';')
			put_semicolon(&index, line, glob);
		else if (line[index] == '<')
			put_input(&index, line, glob);
		else if (line[index] == '>')
		{
			if (line[index + 1] == '>')
				index += put_append(&index, line, glob);
			else
				put_output(&index, line, glob);
		}
		else
			index += put_string(index, line, glob);
		index++;
	}
	return (1);
}
