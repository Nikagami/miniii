/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:25:49 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/30 19:22:11 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_env(char **str)
{
	t_environnement	**env;

	if (*str == NULL)
		return (0);
	env = access_env();
	display_env(env);
	return (0);
}

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	display_env(t_environnement **env)
{
	t_environnement	*cur;

	cur = *env;
	while (cur)
	{
		if (check_equal(cur->str))
		{
			printf("%s\n", cur->str);
		}
		cur = cur->next;
	}
}
