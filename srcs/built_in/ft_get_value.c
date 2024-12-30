/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:19:46 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/30 19:22:11 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_str(char *str)
{
	t_environnement	**env_list;

	env_list = access_env();
	return (lookup_env_str(env_list, str));
}

char	*lookup_env_str(t_environnement **env, char *str)
{
	t_environnement	*cpy;
	int		len;

	len = key_len(str);
	cpy = *env;
	while (cpy)
	{
		if (len == key_len(cpy->str) && !ft_strncmp(cpy->str, str, len))
			return (cpy->str);
		cpy = cpy->next;
	}
	return (NULL);
}

char	*lookup_env(char *str)
{
	t_environnement	**env_list;

	env_list = access_env();
	return (access_env_value(env_list, str));
}

char	*access_env_value(t_environnement **env, char *str)
{
	t_environnement	*cpy;
	int		len;

	len = key_len(str);
	cpy = *env;
	while (cpy)
	{
		if (len == key_len(cpy->str) && !ft_strncmp(cpy->str, str, len))
			return (cpy->str + len + 1);
		cpy = cpy->next;
	}
	return (NULL);
}
