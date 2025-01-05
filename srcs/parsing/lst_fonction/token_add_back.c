/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:29:34 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 10:29:37 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_to_tail(t_token **first, t_token *add_back)
{
	t_token	*cursor;

	cursor = *first;
	if (cursor == NULL)
		*first = add_back;
	else
	{
		while (cursor->next_t)
			cursor = cursor->next_t;
		cursor->next_t = add_back;
	}
}
