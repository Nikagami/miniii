/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:30:59 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/30 19:22:11 by aafounas         ###   ########.fr       */
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
	char	**str;
	t_environnement	*env;
	int		i;
	int		index;

	index = 0;
	i = env_len();
	env = *envp;
	str = malloc(sizeof(char *) * i);
	if (str == NULL)
		return (NULL);
	while (env && index < i)
	{
		str[index] = ft_strdup(env->str);
		if (str[index] == NULL)
			return (NULL);
		index++;
		env = env->next;
	}
	return (str);
}
