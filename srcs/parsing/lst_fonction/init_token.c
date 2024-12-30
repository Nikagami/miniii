/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:21:11 by laclide           #+#    #+#             */
/*   Updated: 2024/12/30 19:24:05 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_token(t_token *new)
{
	new->token_value = NULL;
	new->token_type = TOKEN_NONE;
	new->expanded = false;
	new->next_t = NULL;
}

void	set_token_type(t_token *new)
{
	int	len;

	len = 0;
	if (new->token_value)
		len = ft_strlen(new->token_value);
	if (len == 1)
	{
		if (new->token_value[0] == '<')
			new->token_type = TOKEN_OPEN_FILE;
		else if (new->token_value[0] == '>')
			new->token_type = TOKEN_CREAT_FILE;
	}
	if (len == 2)
	{
		if (new->token_value[0] == '<' && new->token_value[1] == '<')
			new->token_type = TOKEN_HERE_DOC;
		if (new->token_value[0] == '>' && new->token_value[1] == '>')
			new->token_type = TOKEN_WRITE_FILE;
	}
	if (check_builtin(new->token_value))
		new->token_type = TOKEN_BUILTIN;
	if (new->token_type == TOKEN_NONE && len != 0)
		new->token_type = TOKEN_ARG;
}
