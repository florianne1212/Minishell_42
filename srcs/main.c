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
	while (glob->list_env != NULL)
	{
		free(glob->list_env->name);
		free(glob->list_env->value);
		free(glob->list_env);
		glob->list_env = glob->list_env->next;
	}
	free(glob);
}

int			main(int argc, char **argv, char **envp)
{
	t_shell	*glob;

	if (!(glob = malloc(sizeof(t_shell))))
		return (0);
	printf("\nargc %i", argc);
	printf("\nargv %s", argv[0]); //en attendant juste pour ne pas avoir d'erreurs de compilation
	fflush(stdout);
	sort_envp(envp, glob);
	clean_exit(glob);
}
