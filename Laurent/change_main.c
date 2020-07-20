#include "minishell.h"

int main(int argc, char *argv[])
{
	//int i = 0;
	char *abs;
	(void)argc;
	abs = change_rel_to_abs(argv[1]);
	printf("chemin absolu = %s\n", abs);
	free(abs);
	system("leaks a.out | grep 'leaked'");
	//system("leaks a.out");

	return (0);
}