/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/19 22:15:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** la fonction meet permet de verifier si le type
** rencontree correspond a ce qu'on attend
** elle retourne 1 si vrai et 0 si faux
*/

static int		meet(int expect, t_token *tok, t_token_type type)
{
	return ((expect & type) && tok->type == type);
}

/*
** La fonction print_error permet d'afficher les erreurs
** lors de la verification de la ligne de commande
*/

void			print_error(t_token *tok, int expect)
{
	printf("expected (");
	fflush(stdout);
	ft_putnbr_base(tok->type, "01");
	printf("): ");
	if (expect & TT_STRING)
		printf("string, ");
	if (expect & TT_PIPE)
		printf("pipe, ");
	if (expect & TT_APPEND)
		printf("append, ");
	if (expect & TT_OUT)
		printf("out, ");
	if (expect & TT_IN)
		printf("in, ");
	if (expect & TT_SEMICOLOM)
		printf("semicolon, ");
	if (expect & TT_END)
		printf("end of line, ");
	printf("but got: %s (mask ", tok->str);
	fflush(stdout);
	ft_putnbr_base(tok->type, "01");
	printf(")\n");
}

/*
** la fonction validate prmet de verifier si notre ligne de commande est valide
** elle retourne 0 si la ligne de commande n'est pas valide
*/

int		validate(t_shell *glob, int *cmd_count)
{
	t_token		*tok;
	int			expect;
	int			index;

	index = 0;
	expect = TT_STRING;
	while (index < glob->lex->count)
	{
		tok = glob->lex->tokens[index];
		*cmd_count += (tok->type == TT_PIPE || tok->type == TT_SEMICOLOM);
		if (meet(expect, tok, TT_STRING))
			expect = TT_STRING | TT_PIPE | TT_APPEND | TT_OUT | TT_IN | TT_SEMICOLOM | TT_END;
		else if (meet(expect, tok, TT_PIPE))
			expect = TT_STRING;
		else if (meet(expect, tok, TT_APPEND) || meet(expect, tok, TT_OUT) || meet(expect, tok, TT_IN))
			expect = TT_STRING;
		else if (meet(expect, tok, TT_SEMICOLOM))
			expect = TT_STRING | TT_END;
		else if (meet(expect, tok, TT_END))
			expect = 0;
		else
		{
			print_error(tok, expect);
			return (0);
		}
		printf("%d %s\n", index, tok->str);
		index++;
	}
	if (expect != 0)
	{
		printf("unexpected end\n");
		return (0);
	}
	*cmd_count += 1;
	return (1);
}

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
			mode = O_WRONLY | O_CREAT;
	}
	file->path = path;
	file->fd = open(path, mode);
	if (errno != 0)
		file->error = errno;
	errno = 0;
	return (file->error == 0);
}

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
		if (!(glob->cmd[i].argv = (char **)malloc(sizeof(char *))))
			return ;
		glob->cmd[i].argv[0] = NULL;
		i++;
	}
}

int			parser(t_shell *glob, int cmd_count,int cmd_index)
{
	int			index;
	t_token		*t;
	int			i;

	i = 0;
	index = 0;
	while (index < glob->lex->count)
	{
		//printf("\n__%i___\n", cmd_index);
		t = glob->lex->tokens[index];

		if (t->type == TT_STRING)
		{
			if (glob->cmd[cmd_index].exec == NULL)
				glob->cmd[cmd_index].exec = ft_strdup(t->str);
			else
				glob->cmd[cmd_index].argv = add_to_array(glob->cmd[cmd_index].argv, t->str);
		}
		else if (t->type == TT_IN || t->type == TT_OUT || t->type == TT_APPEND)
		{
			if (!open_file(t->type, &(glob->cmd[cmd_index]), glob->lex->tokens[index + 1]->str))
			{
				printf("IN : failed to open file: %s\n", strerror(glob->cmd[cmd_index].in.error));
				printf("OUT: failed to open file: %s\n", strerror(glob->cmd[cmd_index].out.error));
				return (0); // failed to open file
			}
		}
		else if (t->type == TT_PIPE || t->type == TT_SEMICOLOM)
		{
			glob->cmd[cmd_index].pipe = (t->type == TT_PIPE);
			cmd_index += 1;
			printf("\nINDEX IS INCREASED parsing\n");
		}
		else if (t->type == TT_END)
		{
			printf("END --- \n");
			break ;
		}
		index++;
	}
	index = 0;
	i = 0;
	while (index <= cmd_index)
	{
		i = 0;
		printf("cmd {\n");
		printf("    INDEX CMD : %i\n",index);
		printf("	exec	: %s\n", glob->cmd[index].exec);
		while (glob->cmd[index].argv[i] != NULL)
		{
			printf("	argv	: %s\n", glob->cmd[index].argv[i]);
			i++;
		}
		printf("	pipe	: %s\n", glob->cmd[index].pipe ? "true" : "false");
		printf("	in		: %s\n", glob->cmd[index].in.path);
		printf("	out		: %s\n", glob->cmd[index].out.path);
		printf("	append	: %s\n", glob->cmd[index].append ? "true" : "false");
		printf("}\n");
		index++;
		fflush(stdout);
	}
	cmd_count = 0;
	return(cmd_index);
}
