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

/*
** la fonciton nbr_words compte le nombre de mot, ainsi que de separateur
** de "|;<>" elle a tendance a surestimer mais ce n'est pas grave car elle
** sert a mallocer assez d'espace pour le tableau de structure token
*/

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

/*
** comme l'indique son nom la fonction init lex sert a
** initialiser et mallocer la structure lex
*/

void		init_lex(t_shell *glob, char *line)
{
	int		i;

	i = 0;
	if (!(glob->lex = malloc(sizeof(t_lex))))
		return ;
	glob->lex->nb_words = 0;
	glob->lex->tokens = NULL;
	glob->lex->count = 0;
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

/*
** clean_lexer permet de nettoyer la structure lexer
*/

void		clean_lexer(t_shell *glob)
{
	int index;

	index = 0;
	while (index < glob->lex->count)
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

/*
** la fonction put_output permet d'ajouter
** un token dans le tableau de structure
** et de mettre d'assigner TT_END au type
** ca nous sert en partivulier pour les verifs
*/

void		put_end(t_shell *glob)
{
	t_token		*ttok;

	if (!(ttok = malloc(sizeof(t_token))))
		return ;
	ttok->type = TT_END;
	ttok->str = "end";
	glob->lex->tokens[glob->lex->count] = ttok;
	//printf(".%s.", glob->lex->tokens[glob->lex->count]->str);
	glob->lex->count++;
	fflush(stdout);
}

/*
** lexe_line permet de lexer la ligne
** jusqu'a la fin
*/

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
		while (((index + 1) < (int)ft_strlen(line)) &&
		ft_isspace(line[index + 1]) == 1)
			index++;
		index++;
	}
	put_end(glob);
	printf("\n");
	fflush(stdout);
	return (1);
}
