
#include "minishell.h"

static char	*if_no_env(char *str, char *s1, int *current)
{
	char	*new;
	char	*join;
	int		start;

	start = *current;
	while (str[*current] && str[*current] != '"' && str[*current] != '$')
		(*current)++;
	new = malloc(sizeof(char) * ((*current) - start) + 1);
	if (new == NULL)
		return (free_and_nullify(s1));
	new = ft_strncpy(new, str + start, ((*current) - start));
	join = ft_strjoin(s1, new);
	free_strings(s1, new);
	return (join);
}

static char	*if_env(char *str, char *s1, int *current)
{
	char	*env;
	char	*join;

	env = handle_env_var(str, s1, current);
	if (env == NULL)
		return (free_and_nullify(s1));
	join = ft_strjoin(s1, env);
	free_strings(s1, env);
	return (join);
}

char	*process_double_quoted_word(char *str, int *current, char *s1)
{
	while (str && str[*current] && str[*current] != '"')
	{
		if (str[*current] == '$')
		{
			s1 = if_env(str, s1, current);
			if (s1 == NULL)
				return (NULL);
		}
		else
		{
			s1 = if_no_env(str, s1, current);
			if (s1 == NULL)
				return (NULL);
		}
	}
	return (s1);
}
