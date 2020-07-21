/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_and_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:59:31 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/07/21 14:00:53 by lcoiffie         ###   ########.fr       */
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
void child_process(t_shell *glob, char *path, char **arg, char **env)
{
	int	ret;

	ret = execve(path, arg, env);
	glob->retour = ret;
}

void father_process(int child_pid)
{
	int	status;

	waitpid(child_pid, &status, 0);
	printf ("on est revenu dans le pere");
}

int		fork_and_run_command(t_shell *glob, char *path, char **arg, char **env)
{
	pid_t pid;

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
