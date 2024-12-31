/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 19:14:44 by laclide           #+#    #+#             */
/*   Updated: 2024/12/31 15:49:08 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_file_in(t_commande_line **c_list, t_token *current, t_token_type type)
{
	if (type == TOKEN_FILE_IN)
	{
		if ((*c_list)->input_fd != 0)
			close((*c_list)->input_fd);
		(*c_list)->input_fd = open(current->token_value, O_RDONLY);
		if ((*c_list)->input_fd == -1)
		{
			write(1, "minishell: ", 11);
			perror(current->token_value);
			return (-1);
		}
	}
	else if (type == TOKEN_LIMITOR)
	{
		if ((*c_list)->input_fd != 0)
			close((*c_list)->input_fd);
		(*c_list)->input_fd = setup_heredoc_fd(c_list, &current);
		if ((*c_list)->input_fd == -1)
			return (-1);
	}
	return (0);
}

int	redirect_file_out(t_commande_line **c_list, t_token *current, t_token_type type)
{
	if (type == TOKEN_FILE_OUT)
	{
		if ((*c_list)->output_fd != 1)
			close((*c_list)->output_fd);
		(*c_list)->output_fd = open(current->token_value, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if ((*c_list)->output_fd == -1)
			return (-1);
	}
	else if (type == TOKEN_FILE_OUT_APPEND)
	{
		if ((*c_list)->output_fd != 1)
			close((*c_list)->output_fd);
		(*c_list)->output_fd = open(current->token_value, O_CREAT | O_RDWR | O_APPEND, 0644);
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
		if (current->token_type == TOKEN_FILE_IN || current->token_type == TOKEN_LIMITOR)
			if (redirect_file_in(c_list, current, current->token_type) == -1)
				return (-1);
		if (current->token_type == TOKEN_FILE_OUT || current->token_type == TOKEN_FILE_OUT_APPEND)
			if (redirect_file_out(c_list, current, current->token_type) == -1)
				return (-1);
		current = current->next_t;
	}
	return (0);
}
