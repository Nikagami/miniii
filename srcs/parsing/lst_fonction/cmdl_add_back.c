
#include "minishell.h"

void	lst_add_back(t_commande_line **first, t_commande_line *add_back)
{
	t_commande_line	*cursor;

	cursor = *first;
	if (cursor == NULL)
		*first = add_back;
	else
	{
		while (cursor->next_cmd)
			cursor = cursor->next_cmd;
		cursor->next_cmd = add_back;
	}
}
