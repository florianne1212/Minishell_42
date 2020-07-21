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

// int		meet(int expect, t_token *tok, t_token_type type)
// {
// 	return((expect & type) && tok->type == type);
// 	// retourne 1 si vrai et 0 si faux 
// }

// int		check_valid(t_shell *glob, int *cmd_count)
// {
// 	t_token	*tok;
// 	int		index;
// 	int		expect;

// 	expect =  TT_STRING;
// 	index = 0;
// 	while (index < glob->lex->count)
// 	{
// 		tok = glob->lex->tokens[index];
// 		*cmd_count += (tok->type == TT_PIPE || tok->type == TT_SEMICOLOM);

// 		if(meet(expect, tok, TT_STRING))
// 			expect = TT_STRING | TT_PIPE | TT_APPEND | TT_OUT | TT_IN | TT_SEMICOLOM;
// 		else if (meet(expect, tok, TT_PIPE))
// 			expect = TT_STRING;
// 		else if (meet(expect, tok, TT_APPEND) || meet(expect, tok, TT_OUT) || meet(expect, tok, TT_IN))
// 			expect = TT_STRING;
// 		else if (meet(expect, tok, TT_SEMICOLOM))
// 			expect = TT_STRING | TT_END;
// 		else if (meet(expect, tok, TT_END))
// 			expect = 0;
// 		else
// 		{
// 			printf("expected (");
// 			fflush(stdout);
// 			ft_putnbr_base(tok->type, "01");
// 			printf("): ");

// 			if (expect & TT_STRING)
// 				printf("string, ");
// 			if (expect & TT_PIPE)
// 				printf("pipe, ");
// 			if (expect & TT_APPEND)
// 				printf("append, ");
// 			if (expect & TT_OUT)
// 				printf("out, ");
// 			if (expect & TT_IN)
// 				printf("in, ");
// 			if (expect & TT_SEMICOLOM)
// 				printf("semicolon, ");
// 			if (expect & TT_END)
// 				printf("end of line, ");

// 			printf("but got: %s (mask ", tok->str);
// 			fflush(stdout);
// 			ft_putnbr_base(tok->type, "01");
// 			printf(")\n");
// 			return (0);
// 		}

// 		printf("%d %s\n", index, tok->str);
// 		index++;
// 	}
// 	*cmd_count +=1;
// 	return(1);
	
// }

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

	if (expect != 0)
	{
		printf("unexpected end\n");
		return (0);
	}

	*cmd_count += 1;
	return (1);
}


void
parser(t_shell *glob, int index)
{
	int	cmd_count;

	cmd_count = 0;
	(void)index;
	validate(glob, &cmd_count);
}
// static int
// meet(int expect, t_token *tok, t_token_type type)
// {
// 	//  1001001
// 	//& 0000001
// 	//  0000001

// 	return ((expect & type) && tok->type == type);
// }


// static
// int validate(t_shell *glob, int *cmd_count)
// {
// 	t_token *tok;
// 	int expect;

// 	expect = TT_STRING;
// 	for (int index = 0; index < glob->lex->count; ++index)
// 	{
// 		tok = glob->lex->tokens[index];

// 		*cmd_count += (tok->type == TT_PIPE || tok->type == TT_SEMICOLOM);

// 		if (meet(expect, tok, TT_STRING))
// 			expect = TT_STRING | TT_PIPE | TT_APPEND | TT_OUT | TT_IN | TT_SEMICOLOM | TT_END;
// 		else if (meet(expect, tok, TT_PIPE))
// 			expect = TT_STRING;
// 		else if (meet(expect, tok, TT_APPEND) || meet(expect, tok, TT_OUT) || meet(expect, tok, TT_IN))
// 			expect = TT_STRING;
// 		else if (meet(expect, tok, TT_SEMICOLOM))
// 			expect = TT_STRING | TT_END;
// 		else if (meet(expect, tok, TT_END))
// 			expect = 0;
// 		else
// 		{
// 			printf("expected (");
// 			fflush(stdout);
// 			ft_putnbr_base(tok->type, "01");
// 			printf("): ");

// 			if (expect & TT_STRING)
// 				printf("string, ");
// 			if (expect & TT_PIPE)
// 				printf("pipe, ");
// 			if (expect & TT_APPEND)
// 				printf("append, ");
// 			if (expect & TT_OUT)
// 				printf("out, ");
// 			if (expect & TT_IN)
// 				printf("in, ");
// 			if (expect & TT_SEMICOLOM)
// 				printf("semicolon, ");
// 			if (expect & TT_END)
// 				printf("end of line, ");

// 			printf("but got: %s (mask ", tok->str);
// 			fflush(stdout);
// 			ft_putnbr_base(tok->type, "01");
// 			printf(")\n");
// 			return (0);
// 		}

// 		printf("%d %s\n", index, tok->str);
// 	}

// 	*cmd_count += 1;
// 	return (1);
// }

// static int
// open_file(t_token_type type, t_command *cmd, char *path)
// {
// 	t_file *file;
// 	int mode;

// 	if (type == TT_IN)
// 	{
// 		file = &(cmd->in);
// 		mode = O_RDONLY;
// 	}
// 	else
// 	{
// 		file = &(cmd->out);
// 		if ((cmd->append = (type == TT_APPEND)))
// 			mode = O_WRONLY | O_APPEND | O_CREAT;
// 		else
// 			mode = O_WRONLY | O_CREAT;
// 	}

// 	file->path = path;
// 	file->fd = open(path, mode);

// 	if (errno != 0)
// 		file->error = errno;
// 	errno = 0;

// 	return (file->error == 0);
// }

// //	nb_command(glob);
// //	recu_parser(glob, index, 0);
// void
// parser(t_shell *glob, int index)
// {
// 	int			cmd_index;
// 	int			cmd_count;
// 	t_token		*t;

// 	cmd_count = 0;
// 	if (!(validate(glob, &cmd_count)))
// 	{
// 		printf("syntax error\n");
// 		return;
// 	}

// 	glob->cmd = malloc(sizeof(t_command) * cmd_count);
// 	ft_memset(glob->cmd, 0, sizeof(t_command) * cmd_count);

// 	cmd_index = 0;

// 	for (int index = 0; index < glob->lex->count; ++index)
// 	{
// 		t = glob->lex->tokens[index];

// 		if (t->type == TT_STRING)
// 		{
// 			if (glob->cmd[cmd_index].exec == NULL)
// 				glob->cmd[cmd_index].exec = ft_strdup(t->str);
// 			else
// 				; // TODO glob->cmd[cmd_index].argv += ft_strdup(tok->str);
// 		}
// 		else if (t->type == TT_IN || t->type == TT_OUT || t->type == TT_APPEND)
// 		{
// 			if (!open_file(t->type, &(glob->cmd[cmd_index]), glob->lex->tokens[index + 1]->str))
// 			{
// 				printf("IN : failed to open file: %s\n", strerror(glob->cmd[cmd_index].in.error));
// 				printf("OUT: failed to open file: %s\n", strerror(glob->cmd[cmd_index].out.error));
// 				return; // failed to open file
// 			}
// 		}
// 		else if (t->type == TT_PIPE || t->type == TT_SEMICOLOM)
// 		{
// 			glob->cmd[cmd_index].pipe = (t->type == TT_PIPE);
// 			cmd_index++;
// 		}
// 		else if (t->type == TT_END)
// 		{
// 			printf("END --- \n");
// 			break;
// 		}
// 	}

// 	for (int index = 0; index < cmd_count; ++index)
// 	{
// 		printf("cmd {\n");
// 		printf("	exec	: %s\n", glob->cmd[index].exec);
// 		printf("	pipe	: %s\n", glob->cmd[index].pipe ? "true" : "false");
// 		printf("	in		: %s\n", glob->cmd[index].in.path);
// 		printf("	out		: %s\n", glob->cmd[index].out.path);
// 		printf("	append	: %s\n", glob->cmd[index].append ? "true" : "false");
// 		printf("}\n");
// 	}


// }
