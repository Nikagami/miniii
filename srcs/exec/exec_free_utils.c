/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:24:58 by viporten          #+#    #+#             */
/*   Updated: 2024/12/30 17:32:40 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_and_exit(t_commande_line **first)
{
	cleanup_fds(first);
	exit (50);
}

void	free_resources_and_exit(char **str, t_commande_line **first)
{
	free(str);
	cleanup_fds(first);
	exit (50);
}

void	exit_on_error(char **str)
{
	free(str);
	exit(1);
}

void	cleanup_all_and_exit(t_commande_line **cmd,
	pid_t *pid, char **str)
{
	free_all_cmds(cmd);
	free_env();
	free(pid);
	free(str);
	exit(1);
}

void	rm_and_free_file(char *file_name)
{
	if (file_name != NULL)
	{
		unlink(file_name);
		free(file_name);
	}
}
