
#include "minishell.h"

int	count_cmds(t_commande_line *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next_cmd;
	}
	return (i);
}
