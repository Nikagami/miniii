

#include "minishell.h"

int	rm_env(char *s)
{
	return (handle_env_actions(s, ENV_DELETE));
}

void	rm_env_call(t_environnement **env, char *key)
{
	t_environnement	*previous;
	t_environnement	*copy;
	int		len;

	len = key_len(key);
	previous = NULL;
	copy = *env;
	while (copy)
	{
		if (len == key_len(copy->str) && !ft_strncmp(copy->str, key, len))
		{
			if (previous == NULL)
				*env = copy->next;
			else
				previous->next = copy->next;
			free_env_node(copy);
			return ;
		}
		previous = copy;
		copy = copy->next;
	}
}
