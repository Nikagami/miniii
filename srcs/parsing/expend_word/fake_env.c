/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:27:07 by laclide           #+#    #+#             */
/*   Updated: 2024/12/30 18:58:26 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dup_fake_env(char *str)
{
	int		i;
	char	*cpy;

	i = get_fake_env_length(str);
	cpy = malloc(sizeof(char) * (i + 1));
	if (cpy == NULL)
		return (NULL);
	cpy = ft_strncpy(cpy, str, i);
	return (cpy);
}

char	*create_fake_env(int *j, int len_str)
{
	char	*new;

	new = NULL;
	*j = *j + len_str + 1;
	new = malloc(sizeof(char));
	if (new == NULL)
		return (NULL);
	new[0] = '\0';
	return (new);
}

int	get_fake_env_length(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
		i++;
	while (str && str[i] && str[i] != '$')
	{
		if (str[i] && (ft_is_alpha_num(str[i]) == 1) && str[i] != '_')
			return (i + 1);
		i++;
	}
	if (i == 1)
		return (i + 1);
	return (i);
}
