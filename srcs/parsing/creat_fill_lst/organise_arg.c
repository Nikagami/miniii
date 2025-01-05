/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organise_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:30:53 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 10:42:31 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_arg(t_commande_line *cmd)
{
	t_token	*cur_t;
	int		i;

	cur_t = cmd->first_token;
	i = 0;
	while (cur_t)
	{
		if (cur_t->token_type == TOKEN_ARG || \
			cur_t->token_type == TOKEN_BUILTIN)
		{
			cmd->argv[i] = cur_t->t_value;
			i++;
		}
		cur_t = cur_t->next_t;
	}
	cmd->argv[i] = NULL;
}

static int	nbr_arg_cmd(t_commande_line *cmd)
{
	t_token	*cur_t;
	int		len;

	len = 0;
	cur_t = cmd->first_token;
	while (cur_t)
	{
		if (cur_t->token_type == TOKEN_ARG || \
			cur_t->token_type == TOKEN_BUILTIN)
			len++;
		cur_t = cur_t->next_t;
	}
	return (len);
}

int	prepare_cmd_args(t_commande_line **cmd)
{
	t_commande_line	*cur_b;
	int				len_arg;
	char			**new;

	cur_b = *cmd;
	while (cur_b)
	{
		len_arg = nbr_arg_cmd(cur_b);
		new = malloc(sizeof(char *) * (len_arg + 1));
		if (new == NULL)
			return (50);
		cur_b->argv = new;
		init_arg(cur_b);
		cur_b = cur_b->next_cmd;
	}
	return (0);
}
