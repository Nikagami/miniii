/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:16:44 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:31:35 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(void)
{
	handle_env_actions(NULL, ENV_FREE);
}

void	clear_envlist(t_env **env)
{
	t_env	*tmp;
	t_env	*copy;

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

void	free_env_node(t_env *env)
{
	free(env->str);
	free(env);
}
