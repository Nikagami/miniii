/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:16:03 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:25:21 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	wait_for_process(t_commande_line **c_list, pid_t *pid)
{
	int				i;
	int				len;
	t_commande_line	*current;

	i = 0;
	current = *c_list;
	len = count_cmds(current);
	if (len == 1 && check_builtin((*c_list)->argv[0]))
	{
		return (0);
	}
	while (i < len)
	{
		waitpid(pid[i], &g_exit_code, 0);
		if (WIFEXITED(g_exit_code))
			g_exit_code = WEXITSTATUS(g_exit_code);
		else if (WIFSIGNALED(g_exit_code))
		{
			g_exit_code = 128 + WTERMSIG(g_exit_code);
			if (g_exit_code == 131)
				write(2, "Quit\n", ft_strlen("Quit\n"));
		}
		i++;
	}
	return (0);
}

int	run_without_fork(t_commande_line **c_list, pid_t *pid)
{
	if ((*c_list)->argv == NULL)
		return (0);
	else if (run_builtin_fd((*c_list)->argv[0],
			(*c_list)->argv, c_list, pid) != 0)
	{
		return (0);
	}
	return (0);
}

int	process_builtin(char **s, t_commande_line **c_list,
	t_commande_line **head, pid_t *pid)
{
	free(s);
	if (run_builtin((*c_list)->argv[0], (*c_list)->argv, head, pid) == 2)
		exit(1);
	exit(0);
	return (0);
}

void	handle_signal(int sgl)
{
	g_exit_code += sgl;
	if (sgl == 2)
	{
		g_exit_code = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
