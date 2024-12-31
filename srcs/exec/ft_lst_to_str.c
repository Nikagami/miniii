/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:30:59 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/31 15:48:04 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_len(void)
{
	t_environnement	*env;
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

char	**envlist_to_array(t_environnement **envp)
{
	char	**s;
	t_environnement	*env;
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
