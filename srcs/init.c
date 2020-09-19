/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/19 22:15:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** la fonction init_cmd initialise la structure commande
** selon le nombre de "commande" separe par des pipes et des ";"
** enne initialise aussi le tableau d'arguments
*/

void			init_cmd(t_shell *glob, int cmd_count)
{
	int			i;

	i = 0;
	if (!(glob->cmd = malloc(sizeof(t_command) * (cmd_count + 1))))
		return ;
	ft_memset(glob->cmd, 0, sizeof(t_command) * (cmd_count + 1));
	while (i <= cmd_count)
	{
		if (!(glob->cmd[i].cmd_arg = (char **)malloc(sizeof(char *))))
			return ;
		glob->cmd[i].cmd_arg[0] = NULL;
		if (!(glob->cmd[i].argv = (char **)malloc(sizeof(char *))))
			return ;
		glob->cmd[i].argv[0] = NULL;
		glob->cmd[i].error = 0;
		i++;
	}
}

void			init_lex(t_shell *glob, char *line)
{
	if (!(glob->lex = malloc(sizeof(t_lex))))
		return ;
	glob->lex->nb_words = 0;
	glob->lex->tokens = NULL;
	glob->lex->count = 0;
	glob->lex->j = 0;
	glob->lex->e = 0;
	glob->parser_error = 0;
	(void)line;
}

void			init_and_clean(t_shell *glob, int cmd_count)
{
	init_cmd(glob, cmd_count);
	clean_lexer(glob);
}
