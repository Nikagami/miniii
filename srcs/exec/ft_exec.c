/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:24:44 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/31 15:31:37 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>

int	exit_bltin(char **args);

int	ft_non_int(char *str);

int	ft_sup_int(char *str);

extern int	g_exit_code;

int	ft_exec_cmd(t_commande_line **c_list, t_commande_line **head,
	char **s, pid_t *pid)
{
	struct stat	buf;

	execve((*c_list)->argv[0], (*c_list)->argv, s);
	if (stat((*c_list)->argv[0], &buf) == 0)
	{
		write(2, "minishell: ", ft_strlen("minishell: "));
		write(2, (*c_list)->argv[0], ft_strlen((*c_list)->argv[0]));
		write(2, ": Permission denied\n", ft_strlen(": Permission denied\n"));
		exit(126);
	}
	free_all_cmds(head);
	free(s);
	free(pid);
	free_env();
	g_exit_code = 127;
	exit(g_exit_code);
	return (0);
}

int	ft_execve_fct(t_commande_line **c_list, t_commande_line **head, pid_t *pid)
{
	char		**s;

	dup2((*c_list)->input_fd, STDIN_FILENO);
	dup2((*c_list)->output_fd, STDOUT_FILENO);
	cleanup_fds(head);
	s = env_to_array(access_env());
	if (s == NULL)
		cleanup_and_exit(head);
	if (check_builtin((*c_list)->argv[0]) == 0)
	{
		if ((*c_list)->argv[0] == NULL)
			cleanup_all_and_exit(head, pid, s);
		(*c_list)->argv[0] = get_executable_path((*c_list)->argv[0],
				lookup_env("PATH"), 0);
	}
	if ((*c_list)->argv[0] == NULL)
		free_resources_and_exit(s, head);
	rm_and_free_file((*c_list)->file_name);
	if ((*c_list)->input_fd < 0 || (*c_list)->output_fd < 0)
		cleanup_all_and_exit(head, pid, s);
	if (check_builtin((*c_list)->argv[0]))
		process_builtin(s, c_list, head, pid);
	else
		ft_exec_cmd(c_list, head, s, pid);
	return (0);
}

int	multi_fork(pid_t *pid, int i, t_commande_line **c_list, t_commande_line **current)
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
		ft_execve_fct(current, c_list, pid);
	}
	if ((*current)->input_fd != 0)
		close((*current)->input_fd);
	if ((*current)->output_fd != 1)
		close((*current)->output_fd);
	return (0);
}

int	forking(t_commande_line **c_list, pid_t *pid)
{
	t_commande_line	*current;
	int				i;
	int				len;

	i = 0;
	current = *c_list;
	len = count_cmds(current);
	while (current)
	{
		handle_redirections(&current);
		current = current->next_cmd;
	}
	current = *c_list;
	if (len == 1 && check_builtin(current->argv[0]))
	{
		return (run_without_fork(c_list, pid));
	}
	while (i < len)
	{
		multi_fork(pid, i, c_list, &current);
		current = current->next_cmd;
		i++;
	}
	return (0);
}

int	run_commands(t_commande_line **c_list)
{
	t_commande_line	*current;
	int				status_code;
	pid_t			*pid;

	current = *c_list;
	status_code = initialize_pipes(c_list);
	if (status_code != 0)
		return (status_code);
	pid = malloc(sizeof(pid_t) * count_cmds(current));
	if (pid == NULL)
		return (50);
	forking(c_list, pid);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	wait_for_process(c_list, pid);
	signal(SIGINT, handle_cmd_signal);
	signal(SIGQUIT, SIG_IGN);
	free(pid);
	return (0);
}
