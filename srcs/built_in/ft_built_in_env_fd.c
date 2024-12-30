/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_env_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:25:49 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/30 19:22:11 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_fd(char **str, int fd)
{
	t_environnement	**env;

	if (*str == NULL)
		return (0);
	env = access_env();
	display_env_fd(env, fd);
	return (0);
}

void	display_env_fd(t_environnement **env, int fd)
{
	t_environnement	*cur;

	cur = *env;
	while (cur)
	{
		if (check_equal(cur->str))
		{
			ft_putstr_fd(cur->str, fd);
			ft_putchar_fd('\n', fd);
		}
		cur = cur->next;
	}
}
