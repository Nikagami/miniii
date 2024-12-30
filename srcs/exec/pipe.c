/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:54:15 by laclide           #+#    #+#             */
/*   Updated: 2024/12/30 19:24:19 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_nfd(int **nfd)
{
	int	i;

	i = 0;
	while (nfd[i])
	{
		free(nfd[i]);
		i++;
	}
	free(nfd);
}

void	cleanup_fds(t_commande_line **cmdl)
{
	t_commande_line	*cur;

	cur = *cmdl;
	while (cur)
	{
		if (cur->input_fd != 0)
			close(cur->input_fd);
		if (cur->output_fd != 1)
			close(cur->output_fd);
		cur = cur->next_cmd;
	}
}

int	init_pipe(int **nfd, int i, t_commande_line *cur)
{
	nfd[i] = malloc(sizeof(int) * (2));
	if (nfd[i] == NULL)
		return (50);
	if (pipe(nfd[i]) == -1)
		return (40);
	if (i == 0)
		cur->input_fd = 0;
	else
		cur->input_fd = nfd[i - 1][0];
	if (cur->next_cmd == NULL)
	{
		close(nfd[i][0]);
		close(nfd[i][1]);
		cur->output_fd = 1;
	}
	else
		cur->output_fd = nfd[i][1];
	return (0);
}

int	initialize_pipes(t_commande_line **cmdl)
{
	t_commande_line	*cur;
	int				**nfd;
	int				i;
	int				ret;

	i = 0;
	cur = *cmdl;
	nfd = malloc(sizeof(int *) * (count_cmds(cur) + 1));
	if (nfd == NULL)
		return (50);
	nfd[count_cmds(cur)] = NULL;
	while (cur)
	{
		ret = init_pipe(nfd, i, cur);
		if (ret != 0)
		{
			free_nfd(nfd);
			return (ret);
		}
		cur = cur->next_cmd;
		i++;
	}
	free_nfd(nfd);
	return (0);
}
