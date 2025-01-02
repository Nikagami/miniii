#include "minishell.h"

int	free_and_exit(t_commande_line **first, pid_t *pid, int exit_code)
{
	free(pid);
	free_all_cmds(first);
	free_env();
	exit (exit_code);
	return (exit_code);
}
