/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:16:57 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:33:15 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rm_env(char *s)
{
	return (handle_env_actions(s, ENV_DELETE));
}

void	rm_env_call(t_env **env, char *key)
{
	t_env	*previous;
	t_env	*copy;
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
