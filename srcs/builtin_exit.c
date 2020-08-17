
#include "../includes/minishell.h"

int builtin_exit(t_shell *glob, int fd, char **arg)
{
    (void)fd;
    (void)arg;
    glob->running = 0;
    return (0);
}
