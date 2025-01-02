
#include "minishell.h"

int	env_fd(char **s, int fd)
{
	t_environnement	**env;

	if (*s == NULL)
		return (0);
	env = access_env();
	display_env_fd(env, fd);
	return (0);
}

void	display_env_fd(t_environnement **env, int fd)
{
	t_environnement	*current;

	current = *env;
	while (current)
	{
		if (check_equal(current->str))
		{
			ft_putstr_fd(current->str, fd);
			ft_putchar_fd('\n', fd);
		}
		current = current->next;
	}
}
