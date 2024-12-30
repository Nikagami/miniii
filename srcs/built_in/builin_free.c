/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builin_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 20:38:16 by viporten          #+#    #+#             */
/*   Updated: 2024/12/30 17:32:40 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_and_exit(t_commande_line **first, pid_t *pid, int ret)
{
	free(pid);
	free_all_cmds(first);
	free_env();
	exit (ret);
	return (ret);
}
