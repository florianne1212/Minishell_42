/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/09/02 11:14:46 by user42           ###   ########.fr       */
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
		while (ft_strchr_int("<>|;$\'", s[i]) == 1 && s[i] != '\0')
		{
			a++;
			i++;
		}
		if (ft_strchr_int("<>|;$\'", s[i]) == 0 && ft_isspace(s[i]) == 0)
		{
			a++;
			while (ft_strchr_int("<>|$;", s[i]) == 0 &&
			ft_isspace(s[i]) == 0 && s[i] != '\0')
				i++;
		}
	}
	(void)glob;
	return (a);
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
		if (glob->lex->tokens[index]->type)
			free(glob->lex->tokens[index]->str);
		index++;
	}
	index = 0;
	while (index <= glob->lex->count)
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
	ttok->str = ft_strdup("end");
	add_to_2d((void***)&glob->lex->tokens, ttok);
	glob->lex->count++;
}

void		assign_token(int *index, char *line, t_shell *glob, int size)
{
	if (line[*index] == '|')
		put_pipe(index, line, glob);
	else if (line[*index] == ';')
		put_semicolon(index, line, glob);
	else if (line[*index] == '<')
		put_input(index, line, glob);
	else if (line[*index] == '>')
	{
		if (line[*index + 1] == '>')
			put_append(index, line, glob);
		else
			put_output(index, line, glob);
	}
	else
		put_string(index, line, glob);
	while (((*index) < size) &&
	ft_isspace(line[*index]) == 1)
		*index += 1;
}

/*
** lexe_line permet de lexer la ligne
** jusqu'a la fin
*/

int			lexe_line(char *line, t_shell *glob)
{
	int		index;
	int		size;

	size = (int)ft_strlen(line);
	index = 0;
	init_lex(glob, line);
	while (index < size)
	{
		assign_token(&index, line, glob, size);
	}
	put_end(glob);
	return (1);
}
