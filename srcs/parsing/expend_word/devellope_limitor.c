/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devellope_limitor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:25:25 by laclide           #+#    #+#             */
/*   Updated: 2024/12/30 19:19:49 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	move_to(char *str, int *i, t_quote_state quote)
{
	if (quote == QUOTE_NONE)
	{
		while (str[(*i)] && str[(*i)] != '\'' && str[(*i)] != '"')
			(*i)++;
	}
	else if (quote == QUOTE_SINGLE)
	{
		while (str[(*i)] && str[(*i)] != '\'')
			(*i)++;
	}
	else if (quote == QUOTE_DOUBLE)
	{
		while (str[(*i)] && str[(*i)] != '"')
			(*i)++;
	}
	return (0);
}

char	*limitor_unquote(char *str, int *i, char *s1, t_quote_state quote)
{
	int		j;
	char	*s2;
	char	*s3;

	s2 = NULL;
	s3 = NULL;
	j = *i;
	move_to(str, i, quote);
	s2 = malloc(sizeof(char) * ((*i) - j + 1));
	if (s2 == NULL)
		return (free_and_nullify(s1));
	s2 = ft_strncpy(s2, str + j, (*i) - j);
	s3 = ft_strjoin(s1, s2);
	free_strings(s1, s2);
	if (s3 == NULL)
		return (NULL);
	return (s3);
}

char	*expand_full_quote_str(void)
{
	char	*new;

	new = NULL;
	new = malloc(sizeof(char));
	if (new == NULL)
		return (NULL);
	new[0] = '\0';
	return (new);
}

char	*expand_limitor(t_token *stc, char *str, int i)
{
	char	*expand_str;
	t_quote_state	quote;
	t_quote_state	prec;

	quote = QUOTE_NONE;
	prec = QUOTE_NONE;
	expand_str = NULL;
	while (str && str[i])
	{
		quote = manage_quote_state(str[i], quote);
		if (prec != quote)
			prec = complete_quote_update(stc, &i, quote, &expand_str);
		else
		{
			expand_str = limitor_unquote(str, &i, expand_str, quote);
			if (expand_str == NULL)
				return (NULL);
		}
	}
	if (expand_str == NULL)
		return (expand_full_quote_str());
	return (expand_str);
}

int	handle_limitor(t_token *stc, char *str)
{
	char	*new;

	new = NULL;
	new = expand_limitor(stc, str, 0);
	if (str)
		free(str);
	if (new == NULL)
		return (50);
	stc->token_value = new;
	return (0);
}
