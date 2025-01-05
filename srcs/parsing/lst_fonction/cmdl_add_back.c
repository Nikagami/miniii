/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdl_add_back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:29:50 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 10:29:54 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
