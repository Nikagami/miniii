/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_singletone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:16:52 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:31:35 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	key_len(char *env)
{
	int	i;

	i = 0;
	while (env[i] != '\0' && env[i] != '=')
		i++;
	return (i);
}

int	handle_env_actions(char *str, t_env_action mode)
{
	t_env	**env_list;

	env_list = access_env();
	if (mode == ENV_DELETE)
	{
		rm_env_call(env_list, str);
		return (0);
	}
	if (mode == ENV_FREE)
		clear_envlist(env_list);
	if (mode == ENV_ADD)
	{
		if (new_env_value(env_list, str, 0) == 50)
		{
			clear_envlist(env_list);
			return (50);
		}
	}
	return (0);
}
