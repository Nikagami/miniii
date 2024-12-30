/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:11:00 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/30 16:39:36 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	ft_unset(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (handle_env_actions(str[i], ENV_DELETE) == 50)
			return (50);
		i++;
	}
	g_exit_status = 0;
	return (0);
}
