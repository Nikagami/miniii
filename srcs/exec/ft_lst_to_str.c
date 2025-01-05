/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:15:47 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:32:15 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_len(void)
{
	t_env	*env;
	int		i;

	i = 1;
	env = *access_env();
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**envlist_to_array(t_env **envp)
{
	char	**s;
	t_env	*env;
	int		i;
	int		env_index;

	env_index = 0;
	i = env_len();
	env = *envp;
	s = malloc(sizeof(char *) * i);
	if (s == NULL)
		return (NULL);
	while (env && env_index < i)
	{
		s[env_index] = ft_strdup(env->str);
		if (s[env_index] == NULL)
			return (NULL);
		env_index++;
		env = env->next;
	}
	return (s);
}
