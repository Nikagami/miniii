/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_env_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:25:49 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/31 17:43:50 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_fd(char **s, int fd)
{
	t_environnement	**env;

	if (*s == NULL)
		return (0);
	env = access_env();
	display_env_fd(env, fd);
	return (0);
}

void	display_env_fd(t_environnement **env, int fd)
{
	t_environnement	*current;

	current = *env;
	while (current)
	{
		if (check_equal(current->str))
		{
			ft_putstr_fd(current->str, fd);
			ft_putchar_fd('\n', fd);
		}
		current = current->next;
	}
}
