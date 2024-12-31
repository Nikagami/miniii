/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:18:11 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/31 17:36:36 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_add(char *s)
{
	return (handle_env_actions(s, ENV_ADD));
}

char	*rm_plus(char *env)
{
	char	*s;
	int		y;
	int		i;
	int		env_len;

	i = 0;
	y = 0;
	env_len = key_len(env) - 1;
	if (env[key_len(env) - 1] != '+')
		return (ft_strdup(env));
	s = malloc(sizeof(char) * ft_strlen(env));
	if (s == NULL)
		return (NULL);
	while (env[y])
	{
		s[i] = env[y];
		i++;
		y++;
		if (y == env_len)
			y++;
	}
	s[i] = '\0';
	return (s);
}

int	ft_special_lenkey(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '=' && s[i] != '+')
		i++;
	return (i);
}

int	new_env_value(t_environnement **env_list, char *env, int declare)
{
	int		len;
	t_environnement	*copy;

	copy = *env_list;
	len = ft_special_lenkey(env);
	while (copy)
	{
		declare = copy->declare_status;
		if (len == key_len(copy->str) && !ft_strncmp(env, copy->str, len))
		{
			if (has_equal(copy->str) && !has_equal(env))
				return (0);
			free(copy->str);
			copy->str = rm_plus(env);
			if (copy->str == NULL)
			{
				clear_envlist(access_env());
				return (50);
			}
			return (0);
		}
		copy = copy->next;
	}
	return (add_env_front(env, env_list, declare));
}
