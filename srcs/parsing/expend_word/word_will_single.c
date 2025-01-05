/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_will_single.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:30:04 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 10:30:07 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_single_quoted_word(char *str, int *i, char *s1)
{
	char	*s2;
	char	*s3;
	int		j;

	s2 = NULL;
	s3 = NULL;
	j = *i;
	while (str && str[(*i)] && str[(*i)] != '\'')
		(*i)++;
	s2 = malloc(sizeof(char) * ((*i) - j + 1));
	if (s2 == NULL)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	s2 = ft_strncpy(s2, str + j, (*i) - j);
	s3 = ft_strjoin(s1, s2);
	free_strings(s1, s2);
	return (s3);
}
