/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 19:35:40 by laclide           #+#    #+#             */
/*   Updated: 2024/12/30 19:22:11 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_array(t_environnement **envp)
{
	char	**new;
	t_environnement	*cur;
	int		i;

	i = 0;
	cur = *envp;
	while (cur)
	{
		cur = cur->next;
		i++;
	}
	new = malloc(sizeof(char *) * (i + 1));
	new[i] = NULL;
	cur = *envp;
	i = 0;
	while (cur)
	{
		new[i] = cur->str;
		i++;
		cur = cur->next;
	}
	return (new);
}
