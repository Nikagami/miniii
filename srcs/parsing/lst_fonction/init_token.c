/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:29:44 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:38:11 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_token(t_token *new)
{
	new->t_value = NULL;
	new->token_type = TOKEN_NONE;
	new->expanded = false;
	new->next_t = NULL;
}

void	set_token_t(t_token *new)
{
	int	len;

	len = 0;
	if (new->t_value)
		len = ft_strlen(new->t_value);
	if (len == 1)
	{
		if (new->t_value[0] == '<')
			new->token_type = TOKEN_OPEN_FILE;
		else if (new->t_value[0] == '>')
			new->token_type = TOKEN_CREAT_FILE;
	}
	if (len == 2)
	{
		if (new->t_value[0] == '<' && new->t_value[1] == '<')
			new->token_type = TOKEN_HERE_DOC;
		if (new->t_value[0] == '>' && new->t_value[1] == '>')
			new->token_type = TOKEN_WRITE_FILE;
	}
	if (check_builtin(new->t_value))
		new->token_type = TOKEN_BUILTIN;
	if (new->token_type == TOKEN_NONE && len != 0)
		new->token_type = TOKEN_ARG;
}
