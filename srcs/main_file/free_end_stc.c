/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_end_stc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 23:24:45 by viporten          #+#    #+#             */
/*   Updated: 2024/12/31 15:25:30 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	free_cmd_tokens(t_commande_line **cmd_line)
{
	t_token	*tok;

	while ((*cmd_line)->first_token)
	{
		tok = (*cmd_line)->first_token->next_t;
		if ((*cmd_line)->first_token->token_value)
			free((*cmd_line)->first_token->token_value);
		free((*cmd_line)->first_token);
		(*cmd_line)->first_token = tok;
	}
}

int	free_all_cmds(t_commande_line **cmd_line)
{
	t_commande_line	*tmp;

	if (cmd_line)
	{
		while (*cmd_line)
		{
			tmp = (*cmd_line)->next_cmd;
			if ((*cmd_line)->command_strings)
				free((*cmd_line)->command_strings);
			if ((*cmd_line)->argv)
				free((*cmd_line)->argv);
			if ((*cmd_line)->first_token)
				free_cmd_tokens(cmd_line);
			if ((*cmd_line)->file_name)
				free((*cmd_line)->file_name);
			free((*cmd_line));
			*cmd_line = tmp;
		}
	}
	return (1);
}

void	syntax_error_message(void)
{
	write(2, "minishell: syntax error near unexpected token '|' \n",
		ft_strlen("minishell: syntax error near unexpected token '|' \n"));
	g_exit_code = 2;
}
