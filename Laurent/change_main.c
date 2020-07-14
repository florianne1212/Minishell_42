#include "minishell.h"

int main(int argc, char *argv[])
{
	//int i = 0;

	(void)argc;
	change_rel_to_abs(argv[1]);
	system("leaks a.out | grep 'leaked'");
	//system("leaks a.out");

	return (0);
}