/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:21:22 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/30 19:22:11 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rm_env(char *str)
{
	return (handle_env_actions(str, ENV_DELETE));
}

void	rm_env_call(t_environnement **env, char *key)
{
	t_environnement	*cpy;
	t_environnement	*prev;
	int		len;

	len = key_len(key);
	prev = NULL;
	cpy = *env;
	while (cpy)
	{
		if (len == key_len(cpy->str) && !ft_strncmp(cpy->str, key, len))
		{
			if (prev == NULL)
				*env = cpy->next;
			else
				prev->next = cpy->next;
			free_env_node(cpy);
			return ;
		}
		prev = cpy;
		cpy = cpy->next;
	}
}
