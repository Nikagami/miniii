/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 19:35:40 by laclide           #+#    #+#             */
/*   Updated: 2024/12/31 15:55:56 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_array(t_environnement **envp)
{
	char	**env_array;
	t_environnement	*current;
	int		i;

	i = 0;
	current = *envp;
	while (current)
	{
		current = current->next;
		i++;
	}
	env_array = malloc(sizeof(char *) * (i + 1));
	env_array[i] = NULL;
	current = *envp;
	i = 0;
	while (current)
	{
		env_array[i] = current->str;
		i++;
		current = current->next;
	}
	return (env_array);
}
