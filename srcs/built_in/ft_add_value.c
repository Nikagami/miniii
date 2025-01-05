/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:17:55 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:34:03 by trgaspar         ###   ########.fr       */
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

int	new_env_value(t_env **env_list, char *env, int declare)
{
	int		len;
	t_env	*copy;

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
