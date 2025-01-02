
#include "minishell.h"

int	free_cmd_and_ret_err(t_commande_line *stc)
{
	if (stc)
		free(stc);
	return (50);
}

int	clean_token_and_rep_err(t_token *tok)
{
	if (tok)
		free(tok);
	return (50);
}

char	*free_and_nullify(char *s1)
{
	if (s1)
		free(s1);
	return (NULL);
}

void	free_strings(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return ;
}

void	free_and_cleanup_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
	}
	if (split)
		free(split);
}
