
#include "minishell.h"

static void	init_cmdl(t_commande_line *new)
{
	new->command_strings = NULL;
	new->first_token = NULL;
	new->argv = NULL;
	new->file_name = NULL;
	new->next_cmd = NULL;
}

static void	go_to_the_pipe(int *i, char *str)
{
	t_quote_state	quote;

	quote = QUOTE_NONE;
	while (str[*i])
	{
		quote = manage_quote_state(str[*i], quote);
		if (str[*i] == '|' && quote == QUOTE_NONE)
			return ;
		(*i)++;
	}
	return ;
}

static int	create_and_fill_cmd(char *str, int cur, int start,
		t_commande_line **first)
{
	t_commande_line	*new;

	new = malloc(sizeof(t_commande_line));
	if (new == NULL)
		return (50);
	init_cmdl(new);
	new->command_strings = malloc(sizeof(char) * (cur - start + 1));
	if (new->command_strings == NULL)
		return (free_cmd_and_ret_err(new));
	new->command_strings = ft_strncpy(new->command_strings, str + start, cur - start);
	lst_add_back(first, new);
	return (0);
}

int	cmd_line_process(char *string, t_commande_line **first_stc)
{
	int	cur;
	int	start;

	cur = 0;
	start = 0;
	while (string[cur])
	{
		if (cur != 0)
		{
			cur++;
			start++;
		}
		go_to_the_pipe(&cur, string);
		if (create_and_fill_cmd(string, cur, start, first_stc) > 0)
			return (50);
		start = cur;
		if (cur == 0)
		{
			cur++;
			start++;
		}
	}
	return (0);
}
