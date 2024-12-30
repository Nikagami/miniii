/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environnement_singletone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 08:59:11 by victor            #+#    #+#             */
/*   Updated: 2024/12/30 19:18:12 by aafounas         ###   ########.fr       */
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

int	handle_env_actions(char *str, t_environnement_action mode)
{
	t_environnement	**env_list;

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
