
#include "minishell.h"

void	add_to_tail(t_commande_line **first, t_commande_line *add_back)
{
	t_commande_line	*cur;

	cur = *first;
	if (cur == NULL)
		*first = add_back;
	else
	{
		while (cur->next_cmd)
			cur = cur->next_cmd;
		cur->next_cmd = add_back;
	}
}
