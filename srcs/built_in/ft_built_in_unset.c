/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:11:00 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/31 17:49:03 by aafounas         ###   ########.fr       */
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
