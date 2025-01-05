/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_env_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:17:40 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:31:35 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_fd(char **s, int fd)
{
	t_env	**env;

	if (*s == NULL)
		return (0);
	env = access_env();
	display_env_fd(env, fd);
	return (0);
}

void	display_env_fd(t_env **env, int fd)
{
	t_env	*current;

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
