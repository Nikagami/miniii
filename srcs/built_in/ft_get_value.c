
#include "minishell.h"

char	*process_str(char *s)
{
	t_environnement	**env_list;

	env_list = access_env();
	return (lookup_env_str(env_list, s));
}

char	*lookup_env_str(t_environnement **env, char *s)
{
	int		len;
	t_environnement	*copy;

	len = key_len(s);
	copy = *env;
	while (copy)
	{
		if (len == key_len(copy->str) && !ft_strncmp(copy->str, s, len))
			return (copy->str);
		copy = copy->next;
	}
	return (NULL);
}

char	*lookup_env(char *s)
{
	t_environnement	**env_list;

	env_list = access_env();
	return (access_env_value(env_list, s));
}

char	*access_env_value(t_environnement **env, char *s)
{
	int		len;
	t_environnement	*copy;

	len = key_len(s);
	copy = *env;
	while (copy)
	{
		if (len == key_len(copy->str) && !ft_strncmp(copy->str, s, len))
			return (copy->str + len + 1);
		copy = copy->next;
	}
	return (NULL);
}
