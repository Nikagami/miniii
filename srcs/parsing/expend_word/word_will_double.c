/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_will_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:30:25 by laclide           #+#    #+#             */
/*   Updated: 2024/12/30 19:03:30 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*if_no_env(char *str, char *s1, int *cur)
{
	char	*new;
	char	*join;
	int		start;

	start = *cur;
	while (str[*cur] && str[*cur] != '"' && str[*cur] != '$')
		(*cur)++;
	new = malloc(sizeof(char) * ((*cur) - start));
	if (new == NULL)
		return (free_and_nullify(s1));
	new = ft_strncpy(new, str + start, ((*cur) - start));
	join = ft_strjoin(s1, new);
	free_strings(s1, new);
	return (join);
}

static char	*if_env(char *str, char *s1, int *cur)
{
	char	*env;
	char	*join;

	env = handle_env_var(str, s1, cur);
	if (env == NULL)
		return (free_and_nullify(s1));
	join = ft_strjoin(s1, env);
	free_strings(s1, env);
	return (join);
}

char	*process_double_quoted_word(char *str, int *cur, char *s1)
{
	while (str && str[*cur] && str[*cur] != '"')
	{
		if (str[*cur] == '$')
		{
			s1 = if_env(str, s1, cur);
			if (s1 == NULL)
				return (NULL);
		}
		else
		{
			s1 = if_no_env(str, s1, cur);
			if (s1 == NULL)
				return (NULL);
		}
	}
	return (s1);
}
