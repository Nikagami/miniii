/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:21:22 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/31 17:53:38 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rm_env(char *s)
{
	return (handle_env_actions(s, ENV_DELETE));
}

void	rm_env_call(t_environnement **env, char *key)
{
	t_environnement	*previous;
	t_environnement	*copy;
	int		len;

	len = key_len(key);
	previous = NULL;
	copy = *env;
	while (copy)
	{
		if (len == key_len(copy->str) && !ft_strncmp(copy->str, key, len))
		{
			if (previous == NULL)
				*env = copy->next;
			else
				previous->next = copy->next;
			free_env_node(copy);
			return ;
		}
		previous = copy;
		copy = copy->next;
	}
}
