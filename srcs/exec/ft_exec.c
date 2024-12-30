/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:24:44 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/30 19:24:19 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>

int	exit_bltin(char **args);

int	ft_non_int(char *str);

int	ft_sup_int(char *str);

extern int	g_exit_status;

int	ft_exec_cmd(t_commande_line **cmdl, t_commande_line **first,
	char **str, pid_t *pid)
{
	struct stat	buff;

	execve((*cmdl)->argv[0], (*cmdl)->argv, str);
	if (stat((*cmdl)->argv[0], &buff) == 0)
	{
		write(2, "minishell: ", ft_strlen("minishell: "));
		write(2, (*cmdl)->argv[0], ft_strlen((*cmdl)->argv[0]));
		write(2, ": Permission denied\n", ft_strlen(": Permission denied\n"));
		exit(126);
	}
	free_all_cmds(first);
	free(str);
	free(pid);
	free_env();
	g_exit_status = 127;
	exit(g_exit_status);
	return (0);
}

int	ft_execve_fct(t_commande_line **cmdl, t_commande_line **first, pid_t *pid)
{
	char		**str;

	dup2((*cmdl)->input_fd, STDIN_FILENO);
	dup2((*cmdl)->output_fd, STDOUT_FILENO);
	cleanup_fds(first);
	str = env_to_array(access_env());
	if (str == NULL)
		cleanup_and_exit(first);
	if (check_builtin((*cmdl)->argv[0]) == 0)
	{
		if ((*cmdl)->argv[0] == NULL)
			cleanup_all_and_exit(first, pid, str);
		(*cmdl)->argv[0] = get_executable_path((*cmdl)->argv[0],
				lookup_env("PATH"), 0);
	}
	if ((*cmdl)->argv[0] == NULL)
		free_resources_and_exit(str, first);
	rm_and_free_file((*cmdl)->file_name);
	if ((*cmdl)->input_fd < 0 || (*cmdl)->output_fd < 0)
		cleanup_all_and_exit(first, pid, str);
	if (check_builtin((*cmdl)->argv[0]))
		process_builtin(str, cmdl, first, pid);
	else
		ft_exec_cmd(cmdl, first, str, pid);
	return (0);
}

int	multi_fork(pid_t *pid, int i, t_commande_line **cmdl, t_commande_line **cur)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid[i] = fork();
	if (pid[i] == -1)
		exit(1);
	if (pid[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_execve_fct(cur, cmdl, pid);
	}
	if ((*cur)->input_fd != 0)
		close((*cur)->input_fd);
	if ((*cur)->output_fd != 1)
		close((*cur)->output_fd);
	return (0);
}

int	forking(t_commande_line **cmdl, pid_t *pid)
{
	int				len;
	int				i;
	t_commande_line	*cur;

	i = 0;
	cur = *cmdl;
	len = count_cmds(cur);
	while (cur)
	{
		handle_redirections(&cur);
		cur = cur->next_cmd;
	}
	cur = *cmdl;
	if (len == 1 && check_builtin(cur->argv[0]))
	{
		return (run_without_fork(cmdl, pid));
	}
	while (i < len)
	{
		multi_fork(pid, i, cmdl, &cur);
		cur = cur->next_cmd;
		i++;
	}
	return (0);
}

int	run_commands(t_commande_line **cmdl)
{
	t_commande_line	*cur;
	pid_t			*pid;
	int				ret;

	cur = *cmdl;
	ret = initialize_pipes(cmdl);
	if (ret != 0)
		return (ret);
	pid = malloc(sizeof(pid_t) * count_cmds(cur));
	if (pid == NULL)
		return (50);
	forking(cmdl, pid);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	wait_for_process(cmdl, pid);
	signal(SIGINT, handle_cmd_signal);
	signal(SIGQUIT, SIG_IGN);
	free(pid);
	return (0);
}
