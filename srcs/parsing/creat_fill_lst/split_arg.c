
#include "minishell.h"

static int	create_add_back_token(int cur, int start, char *str,
		t_commande_line **stc)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (50);
	reset_token(new);
	new->token_value = malloc(sizeof(char *) * (cur - start + 1));
	if (new->token_value == NULL)
		return (clean_token_and_rep_err(new));
	new->token_value = ft_strncpy(new->token_value, str + start, cur - start);
	set_token_type(new);
	add_token_to_tail(&((*stc)->first_token), new);
	return (0);
}

static void	iter_to_end_or_redirection(char	*str, int *cur)
{
	char	c;

	c = str[*cur];
	while (str[*cur] && str[*cur] == c)
		(*cur)++;
}

int	iter_to_end_arg(int *cur, char *str)
{
	t_quote_state	quote;

	quote = QUOTE_NONE;
	while (str[(*cur)])
	{
		quote = manage_quote_state(str[*cur], quote);
		if (is_delimiter(str[*cur]) == 1 && quote == QUOTE_NONE)
			break ;
		(*cur)++;
	}
	return (0);
}

/*ici on decoupe la string en arg*/
/*tester create_add_back_token == NULL*/
static int	split_string_cur_cmdl(t_commande_line **stc)
{
	int		cur;
	int		start;
	int		len;

	cur = 0;
	len = 0;
	if ((*stc)->command_strings != NULL)
		len = ft_strlen((*stc)->command_strings);
	while (cur < len)
	{
		while (cur < len && (*stc)->command_strings[cur] == ' ')
			cur++;
		start = cur;
		if ((*stc)->command_strings[cur] && is_redir((*stc)->command_strings[cur]))
			iter_to_end_or_redirection((*stc)->command_strings, &cur);
		else
		{
			iter_to_end_arg(&cur, (*stc)->command_strings);
		}
		if (create_add_back_token(cur, start, (*stc)->command_strings, stc) > 0)
			return (50);
	}
	return (0);
}

/* ici on passe sur chaque commande line et on va les envoyer faire split */
/*la commande line en different token et stocker le mot dans token->str*/
int	tokenize_cmd_lines(t_commande_line **first)
{
	t_commande_line	*cur;

	cur = *first;
	while (cur)
	{
		if (split_string_cur_cmdl(&cur) > 0)
			return (50);
		cur = cur->next_cmd;
	}
	return (0);
}
