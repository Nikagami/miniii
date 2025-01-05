/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_word_utils_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:30:35 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:36:05 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_error_message(t_commande_line *cur_b)
{
	write(2, "minishell: syntax error",
		ft_strlen("minishell: syntax error"));
	if (cur_b)
		write(2, " |\n", 3);
	else
		write(2, " newline\n", 9);
	return (12);
}

t_token_t	change_type_file(t_token_t type, int *file)
{
	*file = 0;
	if (type == TOKEN_OPEN_FILE)
		return (TOKEN_FILE_IN);
	else if (type == TOKEN_CREAT_FILE)
		return (TOKEN_FILE_OUT);
	else if (type == TOKEN_WRITE_FILE)
		return (TOKEN_FILE_OUT_APPEND);
	else if (type == TOKEN_HERE_DOC)
		return (TOKEN_LIMITOR);
	return (TOKEN_NONE);
}
