/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_word_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:30:30 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:38:04 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*initialize_string(char **str, char *duplica, int *current, char **s1)
{
	*s1 = NULL;
	*current = 0;
	*str = ft_strdup(duplica);
	free(duplica);
	if (*str == NULL)
		return (NULL);
	return (*str);
}

int	update_token_string(char *str, t_token **stc, char *s1)
{
	free(str);
	(*stc)->t_value = s1;
	return (0);
}

int	check_file_type(t_token_t type)
{
	if (type == TOKEN_CREAT_FILE || type == TOKEN_WRITE_FILE
		|| type == TOKEN_OPEN_FILE || type == TOKEN_HERE_DOC)
		return (1);
	return (0);
}

int	syntax_error_file(t_token_t type)
{
	write(2, "minishell: syntax error",
		ft_strlen("minishell: syntax error"));
	if (type == TOKEN_NONE)
		write(2, " newline\n", 9);
	if (type == TOKEN_CREAT_FILE)
		write(2, " >\n", 3);
	else if (type == TOKEN_WRITE_FILE)
		write(2, " >>\n", 4);
	else if (type == TOKEN_OPEN_FILE)
		write(2, " <\n", 3);
	else if (type == TOKEN_HERE_DOC)
		write(2, " <<\n", 4);
	return (12);
}

t_token_t	change_file_type(t_token_t type, int *file)
{
	*file = 1;
	return (type);
}
