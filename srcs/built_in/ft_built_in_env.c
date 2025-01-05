/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:17:35 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:31:35 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_env(char **s)
{
	t_env	**env;

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

void	display_env(t_env **env)
{
	t_env	*current;

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
