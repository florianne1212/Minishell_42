/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_and_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:59:31 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/20 15:59:34 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// pid_t create_process(void)
// {
// 	pid_t pid;

// 	errno = 0;
// 	pid = fork();
// 	while (pid == -1 && errno == EAGAIN)
// 		pid = fork();
// 	return (pid);
// }

// int		fork_and_run_command(t_shell *glob, char *path, char **arg, char **env)
// {
// 	pid_t pid;

// 	if((pid = create_process()) == -1)
// 		return (1);
// 	if (pid == 0) /*child process*/
// 		execution
// 	else /*father process*/
// 	{
// 		attente retour fils avec prompt
// 	}



// 	return (0);
// }
