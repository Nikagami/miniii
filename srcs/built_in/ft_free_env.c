
#include "minishell.h"

void	free_env(void)
{
	handle_env_actions(NULL, ENV_FREE);
}

void	clear_envlist(t_environnement **env)
{
	t_environnement	*tmp;
	t_environnement	*copy;

	copy = *env;
	tmp = copy;
	while (copy)
	{
		tmp = copy;
		copy = copy->next;
		free(tmp->str);
		free(tmp);
	}
}

void	free_env_node(t_environnement *env)
{
	free(env->str);
	free(env);
}
