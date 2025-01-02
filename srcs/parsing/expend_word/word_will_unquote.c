
#include "minishell.h"

char	*cleanup_split_and_ret_str(char **split, char *str)
{
	free_and_cleanup_split(split);
	return (str);
}

char	*new_token_env(t_token **stc, char **split, int i)
{
	t_token	*next;
	t_token	*new;

	if ((*stc))
		next = (*stc)->next_t;
	while (split[i])
	{
		new = malloc(sizeof(t_token));
		if (new == NULL)
			return (cleanup_split_and_ret_str(split, NULL));
		reset_token(new);
		new->token_type = TOKEN_ARG;
		new->token_value = ft_strdup(split[i]);
		if (new->token_value == NULL)
			if (new)
				return (free_and_cleanup_split_token(split, new));
		if ((*stc))
			new->next_t = next;
		(*stc)->next_t = new;
		(*stc) = (*stc)->next_t;
		i++;
	}
	free_and_cleanup_split(split);
	return (new->token_value);
}

static char	*if_no_env(char *str, int *i, char *s1)
{
	char	*new;
	char	*join;
	int		start;

	start = *i;
	while (str[(*i)] && str[(*i)] != '\'' && str[(*i)] != '"'
		&& str[(*i)] != '$')
		(*i)++;
	new = malloc(sizeof(char) * ((*i) - start + 1));
	if (new == NULL)
		return (free_and_nullify(s1));
	new = ft_strncpy(new, str + start, ((*i) - start));
	join = ft_strjoin(s1, new);
	free_strings(s1, new);
	return (join);
}

static char	*if_env(t_token **stc, char *str, char *s1, int *i)
{
	char	*env;
	char	**split;
	char	*join;

	env = handle_env_var(str, s1, i);
	if (env == NULL)
		return (free_and_nullify(s1));
	split = ft_strsplit(env, ' ');
	free(env);
	if (split == NULL)
		return (free_and_nullify(s1));
	join = ft_strjoin(s1, split[0]);
	if (s1 == NULL && split[0] == NULL)
	{
		join = malloc(sizeof(char));
		join[0] = '\0';
	}
	free(s1);
	if (split[0] == NULL || split[1] == NULL)
		return (cleanup_split_and_ret_str(split, join));
	(*stc)->token_value = join;
	return (new_token_env(stc, split, 1));
}

char	*process_unquoted_word(t_token **stc, char *str, int *cur, char *s1)
{
	while (str[*cur] && str[*cur] != '\'' && str[*cur] != '"')
	{
		if (str[*cur] != '$')
		{
			s1 = if_no_env(str, cur, s1);
			if (s1 == NULL)
				return (NULL);
		}
		else if (str[*cur] && str[*cur] == '$')
		{
			s1 = if_env(stc, str, s1, cur);
			if (s1 == NULL)
			{
				return (NULL);
			}
		}
	}
	return (s1);
}
