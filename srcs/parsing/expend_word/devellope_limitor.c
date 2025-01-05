/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devellope_limitor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:30:40 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 10:42:31 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	move_to(char *str, int *i, t_quote quote)
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

char	*limitor_unquote(char *str, int *i, char *s1, t_quote quote)
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
	t_quote	quote;
	t_quote	prec;

	quote = QUOTE_NONE;
	prec = QUOTE_NONE;
	expand_str = NULL;
	while (str && str[i])
	{
		quote = manage_quote_state(str[i], quote);
		if (prec != quote)
			prec = end_quote_update(stc, &i, quote, &expand_str);
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
	stc->t_value = new;
	return (0);
}
