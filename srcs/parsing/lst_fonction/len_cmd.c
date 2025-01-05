/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:29:38 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 10:29:41 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_commande_line *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next_cmd;
	}
	return (i);
}
