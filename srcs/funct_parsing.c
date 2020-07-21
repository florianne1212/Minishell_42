/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/19 22:15:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			**find_argv(t_shell *glob, int i)
{
	int j;
	int k;
	char **argv;

	j = i;
	while (j <= glob->lex->count && glob->lex->tokens[j]->type == TT_STRING)
		j++;
	j = j - i;
	printf("--%i--", j);
	if(!(argv = (char **)malloc(sizeof(char *) * (j + 1))))
		return (NULL);
	j = i;
	k = 0;
	while (j <= glob->lex->count && glob->lex->tokens[j]->type == TT_STRING)
	{
		ft_putstr(glob->lex->tokens[j]->str);
		fflush(stdout);
		argv[k] = ft_strdup(glob->lex->tokens[j]->str);
		//printf("\n ____%s____", argv[k]);
		k++;
		j++;
	}
	argv[k] =  NULL;
	return(argv);
}

int				manage_in(t_shell *glob, int i, int cmd_nb)
{
//	if (glob->lex->tokens[i]->type == TT_IN)
//	{
//		if (!(glob->cmd[cmd_nb]->in =  malloc(sizeof(t_file))))
//			return (0);
//		if (glob->lex->tokens[i + 1]->type == TT_STRING)
//		{
//			glob->cmd[cmd_nb]->in->path = glob->lex->tokens[i + 1]->str;
//			glob->cmd[cmd_nb]->in->fd = open(glob->cmd[cmd_nb]->in->path, O_RDONLY);
//		}
//		else
//		{
//			ft_putstr("problem after sign : <");
//			return(0);
//		}
//		if (errno != 0)
//		{
//			glob->cmd[cmd_nb]->in->error = errno;
//			errno = 0;
//		}
//	}
	return(1);
}
