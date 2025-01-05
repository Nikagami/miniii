/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:16:27 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:32:49 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_init_env(t_env **env_list)
{
	char	*s;

	s = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (s == NULL)
		return (50);
	if (add_env_front("SHLVL=1", env_list, 1) == 50)
	{
		clear_envlist(env_list);
		return (50);
	}
	if (add_env_front(s, env_list, 1) == 50)
	{
		free(s);
		clear_envlist(env_list);
		return (50);
	}
	free(s);
	if (add_env_front("OLDPWD", env_list, 1) == 50)
	{
		clear_envlist(env_list);
		return (50);
	}
	return (0);
}

t_env	**access_env(void)
{
	static t_env	*new = NULL;

	return (&new);
}

int	load_env(char **env)
{
	int		i;
	t_env	**env_list;

	env_list = access_env();
	i = 0;
	while (env[i])
		i++;
	if (i == 0)
		if (ft_init_env(env_list) == 50)
			return (50);
	i--;
	while (i >= 0)
	{
		if (add_env_front(env[i], env_list, 0) == 50)
		{
			clear_envlist(env_list);
			return (50);
		}
		i--;
	}
	return (0);
}
