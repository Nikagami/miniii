/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:15:41 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:37:27 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_file_in(t_commande_line **c_list, t_token *cur, t_token_t type)
{
	if (type == TOKEN_FILE_IN)
	{
		if ((*c_list)->input_fd != 0)
			close((*c_list)->input_fd);
		(*c_list)->input_fd = open(cur->t_value, O_RDONLY);
		if ((*c_list)->input_fd == -1)
		{
			write(1, "minishell: ", 11);
			perror(cur->t_value);
			return (-1);
		}
	}
	else if (type == TOKEN_LIMITOR)
	{
		if ((*c_list)->input_fd != 0)
			close((*c_list)->input_fd);
		(*c_list)->input_fd = setup_heredoc_fd(c_list, &cur);
		if ((*c_list)->input_fd == -1)
			return (-1);
	}
	return (0);
}

int	redirect_file_out(t_commande_line **c_list, t_token *cur, t_token_t type)
{
	if (type == TOKEN_FILE_OUT)
	{
		if ((*c_list)->output_fd != 1)
			close((*c_list)->output_fd);
		(*c_list)->output_fd = \
			open(cur->t_value, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if ((*c_list)->output_fd == -1)
			return (-1);
	}
	else if (type == TOKEN_FILE_OUT_APPEND)
	{
		if ((*c_list)->output_fd != 1)
			close((*c_list)->output_fd);
		(*c_list)->output_fd = \
			open(cur->t_value, O_CREAT | O_RDWR | O_APPEND, 0644);
		if ((*c_list)->output_fd == -1)
			return (-1);
	}
	return (0);
}

int	handle_redirections(t_commande_line **c_list)
{
	t_token	*current;

	current = (*c_list)->first_token;
	while (current)
	{
		if (current->token_type == TOKEN_FILE_IN || \
			current->token_type == TOKEN_LIMITOR)
			if (redirect_file_in(c_list, current, current->token_type) == -1)
				return (-1);
		if (current->token_type == TOKEN_FILE_OUT || \
			current->token_type == TOKEN_FILE_OUT_APPEND)
			if (redirect_file_out(c_list, current, current->token_type) == -1)
				return (-1);
		current = current->next_t;
	}
	return (0);
}
