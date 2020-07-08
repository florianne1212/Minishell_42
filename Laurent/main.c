/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/07/09 00:15:20 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char* s = "HOM=E";
	char *ret;

	if (!(glob = malloc(sizeof(t_shell))))
		return (0);
	printf("\nargc %i", argc);
	printf("\nargv %s", argv[0]); //en attendant juste pour ne pas avoir d'erreurs de compilation
	fflush(stdout);
	sort_envp(envp, glob);
	if (!(ret = ft_getenv(glob->list_env, s)) && errno)
		perror("getenv");
	printf("\nla valeur de %s est %s\n", s, ret);
	clean_exit(glob);
}
