/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:13:55 by viporten          #+#    #+#             */
/*   Updated: 2024/12/30 17:40:57 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	wait_for_process(t_commande_line **cmdl, pid_t *pid)
{
	t_commande_line	*cur;
	int				len;
	int				i;

	i = 0;
	cur = *cmdl;
	len = count_cmds(cur);
	if (len == 1 && check_builtin((*cmdl)->argv[0]))
	{
		return (0);
	}
	while (i < len)
	{
		waitpid(pid[i], &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		else if (WIFSIGNALED(g_exit_status))
			g_exit_status = 128 + WTERMSIG(g_exit_status);
		i++;
	}
	return (0);
}

int	run_without_fork(t_commande_line **cmdl, pid_t *pid)
{
	if ((*cmdl)->argv == NULL)
		return (0);
	else if (run_builtin_fd((*cmdl)->argv[0],
			(*cmdl)->argv, cmdl, pid) != 0)
	{
		return (0);
	}
	return (0);
}

int	process_builtin(char **str, t_commande_line **cmdl,
	t_commande_line **first, pid_t *pid)
{
	free(str);
	if (run_builtin((*cmdl)->argv[0], (*cmdl)->argv, first, pid) == 2)
		exit(1);
	exit(0);
	return (0);
}

void	handle_signal(int sig)
{
	g_exit_status += sig;
	if (sig == 2)
	{
		g_exit_status = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
