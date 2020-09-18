/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:47:52 by fcoudert          #+#    #+#             */
/*   Updated: 2020/09/10 12:20:35 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			clean_exit(t_shell *glob)
{
	t_list_env	*ptr;

	while (glob->list_env != NULL)
	{
		ptr = glob->list_env->next;
		free(glob->list_env->name);
		glob->list_env->name = NULL;
		if (glob->list_env->value != NULL)
			free(glob->list_env->value);
		glob->list_env->value = NULL;
		free(glob->list_env);
		glob->list_env = ptr;
	}
	glob->list_env = NULL;
	glob = NULL;
}

int				empty_line(char *line, t_shell *glob)
{
	char		*tmp;
	int			i;

	i = 0;
	tmp = ft_strtrim(line, " \t");
	if (ft_strlen(tmp) != 0)
		i = 1;
	free(tmp);
	if (!i)
		g_retour = glob->return_code;
	return (i);
}

int				main(int argc, char **argv, char **envp)
{
	char		*line;
	int			i;
	t_shell		glob;

	ft_memset(&glob, 0, sizeof(t_shell));
	glob.running = 1;
	sort_envp(envp, &glob);
	manage_shlvl(&glob);
	while (glob.running)
	{
		manage_control(&glob);
		ft_putstr_fd("$>", 2);
		gnl2(0, &line);
		if (empty_line(line, &glob) != 0)
			lex_and_parse(line, &glob);
		free(line);
	}
	i = glob.exit_code;
	clean_exit(&glob);
	(void)argv;
	(void)argc;
	return (i);
}
