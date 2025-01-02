
#include "minishell.h"

char	**env_to_array(t_environnement **envp)
{
	char	**env_array;
	t_environnement	*current;
	int		i;

	i = 0;
	current = *envp;
	while (current)
	{
		current = current->next;
		i++;
	}
	env_array = malloc(sizeof(char *) * (i + 1));
	env_array[i] = NULL;
	current = *envp;
	i = 0;
	while (current)
	{
		env_array[i] = current->str;
		i++;
		current = current->next;
	}
	return (env_array);
}
