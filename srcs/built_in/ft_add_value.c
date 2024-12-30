/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:18:11 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/30 19:25:38 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_add(char *str)
{
	return (handle_env_actions(str, ENV_ADD));
}

char	*rm_plus(char *env)
{
	int		len;
	char	*s;
	int		i;
	int		y;

	i = 0;
	y = 0;
	len = key_len(env) - 1;
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
		if (y == len)
			y++;
	}
	s[i] = '\0';
	return (s);
}

int	ft_special_lenkey(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=' && str[i] != '+')
		i++;
	return (i);
}

int	new_env_value(t_environnement **env_list, char *env, int declare)
{
	int		len;
	t_environnement	*cpy;

	cpy = *env_list;
	len = ft_special_lenkey(env);
	while (cpy)
	{
		declare = cpy->declare_status;
		if (len == key_len(cpy->str) && !ft_strncmp(env, cpy->str, len))
		{
			if (has_equal(cpy->str) && !has_equal(env))
				return (0);
			free(cpy->str);
			cpy->str = rm_plus(env);
			if (cpy->str == NULL)
			{
				clear_envlist(access_env());
				return (50);
			}
			return (0);
		}
		cpy = cpy->next;
	}
	return (add_env_front(env, env_list, declare));
}
