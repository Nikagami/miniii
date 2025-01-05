/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:16:22 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:31:35 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_env_front(char *env, t_env **begin_lst, int declare)
{
	t_env	*new_env_entry;

	new_env_entry = malloc(sizeof(t_env));
	if (new_env_entry == NULL)
		return (50);
	new_env_entry->str = rm_plus(env);
	new_env_entry->declare_status = declare;
	if (new_env_entry->str == NULL)
		return (50);
	new_env_entry->next = *begin_lst;
	*begin_lst = new_env_entry;
	return (0);
}
