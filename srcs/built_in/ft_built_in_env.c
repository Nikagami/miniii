/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:25:49 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/31 17:44:29 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_env(char **s)
{
	t_environnement	**env;

	if (*s == NULL)
		return (0);
	env = access_env();
	display_env(env);
	return (0);
}

int	check_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	display_env(t_environnement **env)
{
	t_environnement	*current;

	current = *env;
	while (current)
	{
		if (check_equal(current->str))
		{
			printf("%s\n", current->str);
		}
		current = current->next;
	}
}
