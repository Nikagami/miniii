/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:28:41 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 10:36:50 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_delimiter(char c)
{
	if (c == ' ' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

t_quote	manage_quote_state(char c, t_quote quote)
{
	if (c == '"')
	{
		if (quote == QUOTE_NONE)
			return (QUOTE_DOUBLE);
		else if (quote == QUOTE_DOUBLE)
			return (QUOTE_NONE);
	}
	else if (c == '\'')
	{
		if (quote == QUOTE_NONE)
			return (QUOTE_SINGLE);
		else if (quote == QUOTE_SINGLE)
			return (QUOTE_NONE);
	}
	return (quote);
}

t_quote	end_quote_update(t_token *stc, int *i, t_quote quote, char **s1)
{
	(*i)++;
	stc->expanded = true;
	if (*s1 == NULL)
	{
		*s1 = malloc(sizeof(char));
		if (*s1 != NULL)
			(*s1)[0] = '\0';
	}
	return (quote);
}

int	quote_not_pair(char	*str)
{
	int		i;
	t_quote	quote;

	i = 0;
	quote = QUOTE_NONE;
	while (str[i])
	{
		if (str[i] == '"')
		{
			if (quote == QUOTE_NONE)
				quote = QUOTE_DOUBLE;
			else if (quote == QUOTE_DOUBLE)
				quote = QUOTE_NONE;
		}
		if (str[i] == '\'')
		{
			if (quote == QUOTE_NONE)
				quote = QUOTE_SINGLE;
			else if (quote == QUOTE_SINGLE)
				quote = QUOTE_NONE;
		}
		i++;
	}
	return (quote);
}
