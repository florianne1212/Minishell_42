/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_and_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoiffie <lcoiffie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:59:31 by lcoiffie          #+#    #+#             */
/*   Updated: 2020/08/15 15:02:11 by lcoiffie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**c'est la patie brouillon a bcp remanier
*/

#include "../includes/minishell.h"

/*
**-------create process)-------
** create new process with protections
** je ne l'utilise pas, enzo le trouve dangeureux ( le fork dans boucle)
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

/*
** fonction qui capte le signal et efface ce qui apparait sur le terminal
** n est le numero du signal, a envoyer a $? + 128
*/

void got_the_blody_signal(int n)
{
signal(SIGQUIT, got_the_blody_signal);
signal(SIGINT, got_the_blody_signal);
ft_putstr_fd("\b\b  \b\b", 1);
printf(" gotcha!! your (%d) signal is useless \n", n);
}

/*
** taches a accomplir par child
** essentiellement l'execution de la commande, passer la sortie dans le tube de sortie
** recuperer l'entree dans tube d'entreemettre pour $? le retour de execve
*/

void child_process(t_shell *glob, char *path, char **arg, char **env)
{
	int	ret;

	ret = execve(path, arg, env);
	glob->retour = ret;
}

/*
** taches a accomplir par le pere
** pipe entrees sortie vers child
** signaux ?
*/

void father_process(int child_pid)
{
	int	status;

	(void)child_pid;
	waitpid(child_pid, &status, 0);
	printf ("on est revenu dans le pere, youpi\n");
}

/*
** comme son nom l'indique fait un fork puis execute la commande dans le fils
**
*/
int		fork_and_run_command(t_shell *glob, char *path, char **arg, char **env)
{
	pid_t pid;

	// signal(SIGQUIT, got_the_blody_signal);
	// signal(SIGINT, got_the_blody_signal);

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
