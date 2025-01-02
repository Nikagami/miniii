
#include "minishell.h"

void	add_token_to_tail(t_token **first, t_token *add_back)
{
	t_token	*cur;

	cur = *first;
	if (cur == NULL)
		*first = add_back;
	else
	{
		while (cur->next_t)
			cur = cur->next_t;
		cur->next_t = add_back;
	}
}
