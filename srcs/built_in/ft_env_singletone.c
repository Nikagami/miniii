
#include "minishell.h"

int	key_len(char *env)
{
	int	i;

	i = 0;
	while (env[i] != '\0' && env[i] != '=')
		i++;
	return (i);
}

int	handle_env_actions(char *str, t_environnement_action mode)
{
	t_environnement	**env_list;

	env_list = access_env();
	if (mode == ENV_DELETE)
	{
		rm_env_call(env_list, str);
		return (0);
	}
	if (mode == ENV_FREE)
		clear_envlist(env_list);
	if (mode == ENV_ADD)
	{
		if (new_env_value(env_list, str, 0) == 50)
		{
			clear_envlist(env_list);
			return (50);
		}
	}
	return (0);
}
