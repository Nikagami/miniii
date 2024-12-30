/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 00:26:24 by laclide           #+#    #+#             */
/*   Updated: 2024/12/30 19:24:19 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_modif_two(t_token **stc, char *duplica, t_quote_state quote, t_quote_state prec)
{
	char	*s1;
	int		cur;
	char	*str;

	if (initialize_string(&str, duplica, &cur, &s1) == NULL)
		return (50);
	while (str[cur])
	{
		quote = manage_quote_state(str[cur], quote);
		if (prec != quote)
			prec = complete_quote_update(*stc, &cur, quote, &s1);
		else
		{
			if (quote == QUOTE_SINGLE)
				s1 = process_single_quoted_word(str, &cur, s1);
			else if (quote == QUOTE_DOUBLE)
				s1 = process_double_quoted_word(str, &cur, s1);
			else if (quote == QUOTE_NONE)
				s1 = process_unquoted_word(stc, str, &cur, s1);
		}
		if (s1 == NULL)
			return (free_array_and_ret_err(str));
	}
	return (update_token_string(str, stc, s1));
}

int	word_modif(t_token **stc, char *str, t_token_type token)
{
	t_quote_state	quote;
	t_quote_state	prec;

	quote = QUOTE_NONE;
	prec = QUOTE_NONE;
	if (token == TOKEN_LIMITOR)
		return (handle_limitor(*stc, str));
	return (word_modif_two(stc, str, quote, prec));
}

int	edit_type(t_commande_line **block, int limiter)
{
	t_commande_line	*cur_b;
	t_token			*cur_t;

	cur_b = *block;
	while (cur_b)
	{
		cur_t = cur_b->first_token;
		while (cur_t)
		{
			if (cur_t->token_type == TOKEN_HERE_DOC)
				limiter = 1;
			else if (limiter == 1 && cur_t->token_value && cur_t->token_value[0] != '\0')
			{
				if (check_file_type(cur_t->token_type) == 1)
					return (syntax_error_file(cur_t->token_type));
				cur_t->token_type = TOKEN_LIMITOR;
				limiter = 0;
			}
			cur_t = cur_t->next_t;
		}
		if (limiter == 1)
			return (syntax_error_file(TOKEN_NONE));
		cur_b = cur_b->next_cmd;
	}
	return (0);
}

int	check_open_fil(t_commande_line **block)
{
	t_commande_line	*cur_b;
	t_token			*cur_t;
	int				file;
	t_token_type		type;

	cur_b = *block;
	file = 0;
	while (cur_b)
	{
		cur_t = cur_b->first_token;
		while (cur_t)
		{
			if (check_file_type(cur_t->token_type) == 1 && file == 1)
				return (syntax_error_file(cur_t->token_type));
			else if (check_file_type(cur_t->token_type) == 1)
				type = change_file_type(cur_t->token_type, &file);
			else if (file == 1 && cur_t->token_value && (cur_t->token_value[0] != '\0'))
				cur_t->token_type = change_type_file(type, &file);
			cur_t = cur_t->next_t;
		}
		if (file == 1)
			return (file_error_message(cur_b->next_cmd));
		cur_b = cur_b->next_cmd;
	}
	return (0);
}

int	handle_words_expand(t_commande_line **block)
{
	t_commande_line	*cur_b;
	t_token			*cur_t;
	int				res;

	cur_b = *block;
	if (edit_type(block, 0) != 0 || check_open_fil(block) != 0)
		return (12);
	res = 0;
	while (cur_b)
	{
		cur_t = cur_b->first_token;
		while (cur_t)
		{
			if (cur_t->token_value && cur_t->token_value[0] != '\0')
			{
				res = word_modif(&cur_t, cur_t->token_value, cur_t->token_type);
				if (res != 0)
					return (50);
			}
			cur_t = cur_t->next_t;
		}
		cur_b = cur_b->next_cmd;
	}
	return (0);
}
