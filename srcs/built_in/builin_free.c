/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builin_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:17:59 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:18:00 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_and_exit(t_commande_line **first, pid_t *pid, int exit_code)
{
	free(pid);
	free_all_cmds(first);
	free_env();
	exit (exit_code);
	return (exit_code);
}
