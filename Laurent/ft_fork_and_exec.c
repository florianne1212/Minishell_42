/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_and_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:59:31 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/22 14:08:12 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
**-------create process)-------
** create new process with protections
*/

pid_t create_process(void)
{
	pid_t pid;

	errno = 0;
	pid = fork();
	while (pid == -1 && errno == EAGAIN)
		pid = fork();
	return (pid);
}

void got_the_blody_signal(int n)
{
signal(SIGQUIT, got_the_blody_signal);
signal(SIGINT, got_the_blody_signal);
ft_putstr_fd("\b\b  \b\b", 1);
printf(" gotcha!! your (%d) signal is useless \n", n);
}

void child_process(t_shell *glob, char *path, char **arg, char **env)
{
	int	ret;

	ret = execve(path, arg, env);
	glob->retour = ret;
}

void father_process(int child_pid)
{
	int	status;

	(void)child_pid;
	waitpid(-1, &status, 0);
	printf ("on est revenu dans le pere");
}

int		fork_and_run_command(t_shell *glob, char *path, char **arg, char **env)
{
	pid_t pid;

	signal(SIGQUIT, got_the_blody_signal);
	signal(SIGINT, got_the_blody_signal);

	if((pid = fork())== -1)
		return (1);
	if (pid == 0) /*child process*/
		child_process(glob, path, arg, env);
	else /*father process*/
	{
		father_process(pid);
	}
	return (0);
}

// 	return (0);
// }
