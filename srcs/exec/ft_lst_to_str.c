
#include "minishell.h"

int	env_len(void)
{
	t_environnement	*env;
	int		i;

	i = 1;
	env = *access_env();
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**envlist_to_array(t_environnement **envp)
{
	char	**s;
	t_environnement	*env;
	int		i;
	int		env_index;

	env_index = 0;
	i = env_len();
	env = *envp;
	s = malloc(sizeof(char *) * i);
	if (s == NULL)
		return (NULL);
	while (env && env_index < i)
	{
		s[env_index] = ft_strdup(env->str);
		if (s[env_index] == NULL)
			return (NULL);
		env_index++;
		env = env->next;
	}
	return (s);
}
