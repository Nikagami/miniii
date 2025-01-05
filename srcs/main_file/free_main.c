/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:31:25 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 10:31:28 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_with_cleanup(t_commande_line **cmd)
{
	printf("exit\n");
	free_env();
	return (free_all_cmds(cmd));
}

int	free_resources_on_malloc_error(t_commande_line **cmd, char *str)
{
	free(str);
	free_all_cmds(cmd);
	free_env();
	write(2, "malloc error\n", 13);
	return (50);
}

int	process_error_and_cleanup(t_commande_line **cmd, char *str, int error)
{
	if (error == 40)
		write(2, "pipe fails\n", 11);
	if (error == 50)
		write(2, "malloc error\n", 13);
	free(str);
	free_env();
	free_all_cmds(cmd);
	return (1);
}

void	free_cmd_and_str(t_commande_line **cmd, char *str)
{
	if (str)
		free(str);
	free_all_cmds(cmd);
}

int	cleanup_on_malloc_fail(t_commande_line **cmd, char *str)
{
	free(str);
	free_all_cmds(cmd);
	return (50);
}
