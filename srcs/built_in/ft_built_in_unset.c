/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:17:07 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:17:10 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	ft_unset(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		if (handle_env_actions(s[i], ENV_DELETE) == 50)
			return (50);
		i++;
	}
	g_exit_code = 0;
	return (0);
}
