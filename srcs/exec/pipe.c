/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:54:15 by laclide           #+#    #+#             */
/*   Updated: 2024/12/31 15:54:07 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fd_list(int **fd_list)
{
	int	i;

	i = 0;
	while (fd_list[i])
	{
		free(fd_list[i]);
		i++;
	}
	free(fd_list);
}

void	cleanup_fds(t_commande_line **c_list)
{
	t_commande_line	*current;

	current = *c_list;
	while (current)
	{
		if (current->input_fd != 0)
			close(current->input_fd);
		if (current->output_fd != 1)
			close(current->output_fd);
		current = current->next_cmd;
	}
}

int	init_pipe(int **pipe_fds, int i, t_commande_line *current)
{
	pipe_fds[i] = malloc(sizeof(int) * (2));
	if (pipe_fds[i] == NULL)
		return (50);
	if (pipe(pipe_fds[i]) == -1)
		return (40);
	if (i == 0)
		current->input_fd = 0;
	else
		current->input_fd = pipe_fds[i - 1][0];
	if (current->next_cmd == NULL)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		current->output_fd = 1;
	}
	else
		current->output_fd = pipe_fds[i][1];
	return (0);
}

int	initialize_pipes(t_commande_line **c_list)
{
	int				i;
	int				status_code;
	t_commande_line	*current;
	int				**pipe_fds;

	i = 0;
	current = *c_list;
	pipe_fds = malloc(sizeof(int *) * (count_cmds(current) + 1));
	if (pipe_fds == NULL)
		return (50);
	pipe_fds[count_cmds(current)] = NULL;
	while (current)
	{
		status_code = init_pipe(pipe_fds, i, current);
		if (status_code != 0)
		{
			free_fd_list(pipe_fds);
			return (status_code);
		}
		current = current->next_cmd;
		i++;
	}
	free_fd_list(pipe_fds);
	return (0);
}
