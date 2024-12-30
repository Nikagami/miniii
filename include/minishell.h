/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:50:47 by viporten          #+#    #+#             */
/*   Updated: 2024/12/30 17:32:40 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../srcs/libft/includes/libft.h"
# include <stdbool.h>
# include "parsing.h"
# include "exec.h"
# include "builtin.h"
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

void	handle_cmd_signal(int sig);
int		exit_with_cleanup(t_commande_line **cmd);

int		free_resources_on_malloc_error(t_commande_line **cmd, char *str);

int		process_error_and_cleanup(t_commande_line **cmd, char *str, int error);

void	free_cmd_and_str(t_commande_line **cmd, char *str);

void	free_cmd_tokens(t_commande_line **cmd_line);
int		cleanup_on_malloc_fail(t_commande_line **cmd, char *str);
void	syntax_error_message(void);
int		free_all_cmds(t_commande_line **cmd_line);
#endif
