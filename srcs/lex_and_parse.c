/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_and_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/09/07 13:57:49 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** clean_cmd permet de nettoyer la structure cmd
*/

void		clean_cmd(t_shell *glob, int cmd_count)
{
	int i;
	int e;

	e = 0;
	i = 0;
	while (i <= cmd_count)
	{
		e = 0;
		while (glob->cmd[i].argv[e] != NULL)
		{
			free(glob->cmd[i].argv[e]);
			glob->cmd[i].argv[e] = NULL;
			e++;
		}
		free(glob->cmd[i].exec);
		free(glob->cmd[i].cmd_arg);
		free(glob->cmd[i].argv);
		i++;
	}
	free(glob->cmd);
}

/*
** lexe_s_colon permet de lexer la ligne j'usqu'au prochain point virgule
** ou a la jusqu'a la fin de la ligne
*/

int			lexe_s_colon(char *line, t_shell *glob, int *index)
{
	init_lex(glob, line);
	while (*index < (int)ft_strlen(line))
	{
		if (line[*index] == ';')
			return (1);
		else if (line[*index] == '|')
			put_pipe(index, line, glob);
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
		while (((*index) < (int)ft_strlen(line)) &&
		ft_isspace(line[*index]) == 1)
			*index += 1;
	}
	return (1);
}

void		arg_in_tab(int i, int cmd_index, t_shell *glob)
{
	while (i <= cmd_index)
	{
		free(glob->cmd[i].cmd_arg);
		glob->cmd[i].cmd_arg = add_front_to_array(glob->cmd[i].argv,
		glob->cmd[i].exec);
		i++;
	}
}

/*
** la fonction lex and validate permet de lexer un premiere fois toute
** la ligne puis de verifier que tout soit bon
*/

int			lex_and_validate(char *line, t_shell *glob)
{
	int		cmd_count;

	cmd_count = 0;
	lexe_line(line, glob);
	if (!(validate(glob, &cmd_count)))
	{
		clean_lexer(glob);
		return (0);
	}
	return (cmd_count);
}

/*
** la fonction lex and parse permet d'envoyer en plusieurs fois les commandes
** si elles sont separee par un point virgule
*/

int			lex_and_parse(char *line, t_shell *glob)
{
	int		cmd_count;
	int		index;
	int		cmd_index;

	index = 0;
	cmd_index = 0;
	if ((cmd_count = lex_and_validate(line, glob)) <= 0)
		return (0);
	init_and_clean(glob, cmd_count);
	while (index < (int)ft_strlen(line))
	{
		glob->tmp_cmd_index = cmd_index;
		lexe_s_colon(line, glob, &index);
		cmd_index = parser(glob, cmd_index);
		clean_lexer(glob);
		arg_in_tab(glob->tmp_cmd_index, cmd_index, glob);
		run_commands(glob->tmp_cmd_index, glob);
		index++;
		cmd_index++;
	}
	if (glob->cmd)
		clean_cmd(glob, cmd_count);
	if (g_retour == 0)
		g_retour = glob->return_code;
	return (0);
}
