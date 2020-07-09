/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoudert <fcoudert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/06/25 22:05:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		clean_exit(t_shell *glob)
{
	t_list_env *ptr;

	while (glob->list_env != NULL)
	{
		ptr = glob->list_env->next;
		free(glob->list_env->name);
		glob->list_env->name = NULL;
		free(glob->list_env->value);
		glob->list_env->value = NULL;
		free(glob->list_env);
		glob->list_env = ptr;
	}
	glob->list_env = NULL;
	free(glob);
	glob = NULL;
}

int			main(int argc, char **argv, char **envp)
{
	t_shell	*glob;
	int		i;
	char	buf[100];

	i = 1;
	signal(SIGINT, control_c); //permet d'intercepter le signal envoyer par ctrl-C
	signal(SIGQUIT, control_back); //permet d'intercepter le signal envoyer par ctrl-backslash
	if (!(glob = malloc(sizeof(t_shell))))
		return (0);
	printf("\nargc %i", argc);
	printf("\nargv %s\n", argv[0]); //en attendant juste pour ne pas avoir d'erreurs de compilation
	fflush(stdout);
	sort_envp(envp, glob);
	while (i == 1)
	{
		ft_putstr(">");
		read(1, buf, 10);
		if (strncmp(buf, "exit", 4) == 0)
		{
			i = 0;
		}
	}
	clean_exit(glob);
}
