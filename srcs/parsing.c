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

//void
//free_2d(char **s)
//{
//	int i;
//
//	i = 0;
//	while (ft_strcmp(s[i], "NULL") != 0)
//	{
//		free(s[i]);
//		i++;
//	}
//	free(s[i]);
//	free(s);
//}
//
//void
//init_command(t_shell *glob, int i)
//{
//	if (!(glob->cmd[i] = malloc(sizeof(t_command))))
//		return;
//	glob->cmd[i]->exec = NULL;
//	if (!(glob->cmd[i]->argv = (char**)malloc(sizeof(char*) * (1))))
//		return;
//	glob->cmd[i]->argv[0] = NULL;
//	glob->cmd[i]->pipe = FALSE;
//	glob->cmd[i]->in = NULL;
//	glob->cmd[i]->out = NULL;
//	//glob->cmd->append = NULL;
//}
//
//void
//nb_command(t_shell *glob)
//{
//	int i;
//	int j;
//
//	i = 1;
//	j = 0;
//	while (i <= glob->lex->count /* &&
//	 glob->lex->tokens[i]->type != TT_SEMICOLOM*/)
//	{
//		if (glob->lex->tokens[i]->type == TT_PIPE || glob->lex->tokens[i]->type == TT_SEMICOLOM)
//			j++;
//		i++;
//	}
//	if (!(glob->cmd = (t_command**)malloc(sizeof(t_command*) * (j + 2))))
//		return;
//}
//
//void
//recu_parser(t_shell *glob, int index, int cmd_nb)
//{
//	int i = index;
//	init_command(glob, cmd_nb);
//	if (glob->lex->tokens[index]->type != TT_STRING)
//	{
//		ft_putstr("\n Syntax Error");
//		exit(EXIT_SUCCESS);
//	}
//	while (i <= glob->lex->count && glob->lex->tokens[i]->type != TT_SEMICOLOM)
//	{
//		if (i == index)
//			glob->cmd[cmd_nb]->exec = ft_strdup(glob->lex->tokens[i]->str);
//		else if (glob->lex->tokens[i]->type == TT_IN)
//		{
//			if (manage_in(glob, i, cmd_nb) != 0)
//				i += 1;
//		}
//		else if (glob->lex->tokens[i]->type == TT_OUT)
//		{
//			if (manage_out(glob, i) != 0)
//				i += 1;
//		}
//		else if (glob->lex->tokens[i]->type == TT_STRING)
//			glob->cmd[cmd_nb]->argv = add_to_array(glob->cmd[cmd_nb]->argv, glob->lex->tokens[i]->str);
//
//		i++;
//	}
//	int k = 0;
//	printf("\n cmd %i exec = %s", cmd_nb, glob->cmd[cmd_nb]->exec);
//	while (glob->cmd[cmd_nb]->argv[k])
//	{
//		printf("\n cmd %i arg %i = %s", cmd_nb, k, glob->cmd[cmd_nb]->argv[k]);
//		k++;
//	}
//	if (glob->cmd[0]->in != NULL)
//		printf("\n cmd %i in = %s", cmd_nb, glob->cmd[cmd_nb]->in->path);
//	fflush(stdout);
//	if (i <= glob->lex->count && glob->lex->tokens[i]->type == TT_SEMICOLOM)
//	{
//		if (i + 1 <= glob->lex->count)
//			recu_parser(glob, (i + 1), (cmd_nb + 1));
//	}
//	else
//		return;
//	//int k = 0;
//	// fflush(stdout);
//	// free(glob->cmd[0]);
//	// free(glob->cmd);
//	// fflush(stdout);
//}

static int
meet(int expect, t_token *tok, t_token_type type)
{
	//  1001001
	//& 0000001
	//  0000001

	return ((expect & type) && tok->type == type);
}


static
int validate(t_shell *glob, int *cmd_count)
{
	t_token *tok;
	int expect;

	expect = TT_STRING;
	for (int index = 0; index < glob->lex->count; ++index)
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
			return (0);
		}

		printf("%d %s\n", index, tok->str);
	}

	*cmd_count += 1;
	return (1);
}

static int
open_file(t_token_type type, t_command *cmd, char *path)
{
	t_file *file;
	int mode;

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

//	nb_command(glob);
//	recu_parser(glob, index, 0);
void
parser(t_shell *glob, int index)
{
	int			cmd_index;
	int			cmd_count;
	t_token		*t;

	cmd_count = 0;
	if (!(validate(glob, &cmd_count)))
	{
		printf("syntax error\n");
		return;
	}

	glob->cmd = malloc(sizeof(t_command) * cmd_count);
	ft_memset(glob->cmd, 0, sizeof(t_command) * cmd_count);

	cmd_index = 0;

	for (int index = 0; index < glob->lex->count; ++index)
	{
		t = glob->lex->tokens[index];

		if (t->type == TT_STRING)
		{
			if (glob->cmd[cmd_index].exec == NULL)
				glob->cmd[cmd_index].exec = ft_strdup(t->str);
			else
				; // TODO glob->cmd[cmd_index].argv += ft_strdup(tok->str);
		}
		else if (t->type == TT_IN || t->type == TT_OUT || t->type == TT_APPEND)
		{
			if (!open_file(t->type, &(glob->cmd[cmd_index]), glob->lex->tokens[index + 1]->str))
			{
				printf("IN : failed to open file: %s\n", strerror(glob->cmd[cmd_index].in.error));
				printf("OUT: failed to open file: %s\n", strerror(glob->cmd[cmd_index].out.error));
				return; // failed to open file
			}
		}
		else if (t->type == TT_PIPE || t->type == TT_SEMICOLOM)
		{
			glob->cmd[cmd_index].pipe = (t->type == TT_PIPE);
			cmd_index++;
		}
		else if (t->type == TT_END)
		{
			printf("END --- \n");
			break;
		}
	}

	for (int index = 0; index < cmd_count; ++index)
	{
		printf("cmd {\n");
		printf("	exec	: %s\n", glob->cmd[index].exec);
		printf("	pipe	: %s\n", glob->cmd[index].pipe ? "true" : "false");
		printf("	in		: %s\n", glob->cmd[index].in.path);
		printf("	out		: %s\n", glob->cmd[index].out.path);
		printf("	append	: %s\n", glob->cmd[index].append ? "true" : "false");
		printf("}\n");
	}


}
