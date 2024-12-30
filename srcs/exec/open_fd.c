/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 19:14:44 by laclide           #+#    #+#             */
/*   Updated: 2024/12/30 19:24:05 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_file_in(t_commande_line **cmdl, t_token *cur, t_token_type type)
{
	if (type == TOKEN_FILE_IN)
	{
		if ((*cmdl)->input_fd != 0)
			close((*cmdl)->input_fd);
		(*cmdl)->input_fd = open(cur->token_value, O_RDONLY);
		if ((*cmdl)->input_fd == -1)
		{
			write(1, "minishell: ", 11);
			perror(cur->token_value);
			return (-1);
		}
	}
	else if (type == TOKEN_LIMITOR)
	{
		if ((*cmdl)->input_fd != 0)
			close((*cmdl)->input_fd);
		(*cmdl)->input_fd = setup_heredoc_fd(cmdl, &cur);
		if ((*cmdl)->input_fd == -1)
			return (-1);
	}
	return (0);
}

int	redirect_file_out(t_commande_line **cmdl, t_token *cur, t_token_type type)
{
	if (type == TOKEN_FILE_OUT)
	{
		if ((*cmdl)->output_fd != 1)
			close((*cmdl)->output_fd);
		(*cmdl)->output_fd = open(cur->token_value, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if ((*cmdl)->output_fd == -1)
			return (-1);
	}
	else if (type == TOKEN_FILE_OUT_APPEND)
	{
		if ((*cmdl)->output_fd != 1)
			close((*cmdl)->output_fd);
		(*cmdl)->output_fd = open(cur->token_value, O_CREAT | O_RDWR | O_APPEND, 0644);
		if ((*cmdl)->output_fd == -1)
			return (-1);
	}
	return (0);
}

int	handle_redirections(t_commande_line **cmdl)
{
	t_token	*cur;

	cur = (*cmdl)->first_token;
	while (cur)
	{
		if (cur->token_type == TOKEN_FILE_IN || cur->token_type == TOKEN_LIMITOR)
			if (redirect_file_in(cmdl, cur, cur->token_type) == -1)
				return (-1);
		if (cur->token_type == TOKEN_FILE_OUT || cur->token_type == TOKEN_FILE_OUT_APPEND)
			if (redirect_file_out(cmdl, cur, cur->token_type) == -1)
				return (-1);
		cur = cur->next_t;
	}
	return (0);
}
