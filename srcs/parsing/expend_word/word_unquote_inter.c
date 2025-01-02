
#include "minishell.h"

char	*handle_env_var(char *str, char *tmp, int *cur)
{
	char	*tmp2;

	tmp2 = NULL;
	tmp2 = lookup_env_var(cur, str);
	if (tmp2 == NULL)
		return (free_and_nullify(tmp));
	return (tmp2);
}

char	*extract_before_env(char *str, char *s1, int *cur, int start)
{
	char	*s2;
	char	*s3;

	s2 = NULL;
	s3 = NULL;
	s2 = malloc(sizeof(char) * ((*cur) - start + 1));
	if (s2 == NULL)
		return (free_and_nullify(s1));
	s2 = ft_strncpy(s2, str + start, (*cur) - start);
	s3 = ft_strjoin(s1, s2);
	free_strings(s1, s2);
	return (s3);
}

char	*unquote_and_cat(char *str, char *s1, int *i, int j)
{
	char	*s2;
	char	*s3;

	s2 = NULL;
	s3 = NULL;
	if ((*i) - j == 0)
		return (s1);
	s2 = malloc(sizeof(char) * ((*i) - j + 1));
	if (s2 == NULL)
		return (free_and_nullify(s1));
	s2 = ft_strncpy(s2, str + j, (*i) - j);
	s3 = ft_strjoin(s1, s2);
	free_strings(s1, s2);
	return (s3);
}

char	*free_and_cleanup_split_token(char **split, t_token *tok)
{
	free_and_cleanup_split(split);
	if (tok)
	{
		if (tok->token_value)
			free(tok->token_value);
	}
	return (NULL);
}
