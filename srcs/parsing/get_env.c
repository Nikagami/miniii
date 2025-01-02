
#include "minishell.h"

extern int	g_exit_code;

int	access_env_var_len(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$')
		str++;
	if (str[0] && str[0] == '?')
		return (1);
	while (str[i] && (ft_is_alpha_num(str[i]) == 0 || str[i] == '_'))
		i++;
	return (i);
}

int	is_env(char *str, char *env, int len)
{
	int	i;

	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] == '\0' || env[i] == '\0')
			return (-1);
		if (str[i] != env[i])
			return (-1);
		i++;
	}
	if (env[i] && env[i] == '=')
		return (0);
	return (-1);
}

char	*doll_alloc(int *current)
{
	char	*new;

	*current = *current + 1;
	new = malloc(sizeof(char) * 2);
	if (new)
	{
		new[0] = '$';
		new[1] = '\0';
		return (new);
	}
	return (NULL);
}

char	*get_envmtp(char *str, int *current)
{
	int		len_str;
	char	*cpy;
	char	*env;

	cpy = NULL;
	len_str = access_env_var_len(str);
	if (len_str == 0)
		return (doll_alloc(current));
	if (len_str == 1 && str[1] == '?')
	{
		*current = *current + 2;
		return (ft_itoa(g_exit_code));
	}
	cpy = malloc(sizeof(char) * (len_str + 1));
	if (cpy == NULL)
		return (NULL);
	cpy = ft_strncpy(cpy, str + 1, len_str);
	env = lookup_env(cpy);
	free(cpy);
	if (env == NULL)
		return (create_fake_env(current, len_str));
	*current = *current + len_str + 1;
	cpy = ft_strdup(env);
	return (cpy);
}

char	*lookup_env_var(int *current, char *str)
{
	char	*s3;

	s3 = get_envmtp(str + *current, current);
	return (s3);
}
