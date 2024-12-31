/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 20:59:18 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/31 17:54:03 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(void)
{
	handle_env_actions(NULL, ENV_FREE);
}

void	clear_envlist(t_environnement **env)
{
	t_environnement	*tmp;
	t_environnement	*copy;

	copy = *env;
	tmp = copy;
	while (copy)
	{
		tmp = copy;
		copy = copy->next;
		free(tmp->str);
		free(tmp);
	}
}

void	free_env_node(t_environnement *env)
{
	free(env->str);
	free(env);
}
