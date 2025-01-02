
#include "minishell.h"

extern int	g_exit_code;

int	ft_unset(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		if (handle_env_actions(s[i], ENV_DELETE) == 50)
			return (50);
		i++;
	}
	g_exit_code = 0;
	return (0);
}
