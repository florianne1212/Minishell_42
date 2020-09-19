/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/08/31 12:10:43 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** la fonction open_file permet de faire la bonne ouverture
** de fichier correspondant a la commande
** elle retourne 0 si il y a une erreur dans l'ouverture du fichier ou sinon 1
*/

static int		open_file(t_token_type type, t_command *cmd, char *path)
{
	t_file		*file;
	int			mode;

	if (type == TT_IN)
	{
		file = &(cmd->in);
		mode = O_RDONLY;
	}
	else
	{
		file = &(cmd->out);
		if ((cmd->append = (type == TT_APPEND)))
			mode = O_WRONLY | O_APPEND | O_CREAT;
		else
			mode = O_WRONLY | O_CREAT | O_TRUNC;
	}
	file->path = path;
	file->fd = open(path, mode, 0644);
	return (file->fd != -1);
}

/*
** la donction parser_string permet de parser
** les string et de les mettres dans au bon endroit
** dans la structure cmd en fonction si c'est l'executable
** ouu les arguments
*/

void			parser_string(t_shell *glob, int cmd_index, t_token *t)
{
	if (glob->cmd[cmd_index].exec == NULL)
		glob->cmd[cmd_index].exec = ft_strdup(t->str);
	else
		glob->cmd[cmd_index].argv = add_to_array(glob->cmd[cmd_index].argv,
		t->str);
}

/*
** la donction parser_redir permet de parser
** les redirections in, out et append et d'appeller
** la fonction open_fille en consequence
*/

int				parser_redir(t_shell *glob, int cmd_index, t_token *t, int idx)
{
	if (glob->parser_error == 0 && !open_file(t->type, &(glob->cmd[cmd_index]),
	glob->lex->tokens[idx + 1]->str))
	{
		ft_putstr_fd("minishell :", 2);
		ft_putstr_fd(glob->lex->tokens[idx + 1]->str, 2);
		ft_putstr_fd(": Aucun fichier ou dossier de ce type\n", 2);
		glob->cmd[cmd_index].error = 1;
		glob->parser_error = 1;
		return (0);
	}
	return (1);
}

/*
** comme l'indique son nom la fonction parser permet de
** parser les elements precedement lexer et verifier
*/

int				parser(t_shell *glob, int cmd_index)
{
	int			index;
	t_token		*t;

	index = 0;
	while (index < glob->lex->count)
	{
		t = glob->lex->tokens[index];
		if (t->type == TT_STRING)
			parser_string(glob, cmd_index, t);
		else if (t->type == TT_IN || t->type == TT_OUT || t->type == TT_APPEND)
		{
			parser_redir(glob, cmd_index, t, index);
			index++;
		}
		else if (t->type == TT_PIPE || t->type == TT_SEMICOLOM)
		{
			glob->cmd[cmd_index].pipe = (t->type == TT_PIPE);
			cmd_index += 1;
		}
		else if (t->type == TT_END)
			break ;
		index++;
	}
	return (cmd_index);
}
