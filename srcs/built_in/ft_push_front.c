
#include "minishell.h"

int	add_env_front(char *env, t_environnement **begin_lst, int declare)
{
	t_environnement	*new_env_entry;

	new_env_entry = malloc(sizeof(t_environnement));
	if (new_env_entry == NULL)
		return (50);
	new_env_entry->str = rm_plus(env);
	new_env_entry->declare_status = declare;
	if (new_env_entry->str == NULL)
		return (50);
	new_env_entry->next = *begin_lst;
	*begin_lst = new_env_entry;
	return (0);
}
