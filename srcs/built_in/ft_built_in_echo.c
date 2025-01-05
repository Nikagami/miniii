/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:17:46 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:17:47 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	flag_n(char **s)
{
	int	y;
	int	i;
	int	count;

	count = 0;
	y = 0;
	i = 0;
	while (s[i] && ft_strlen(s[i]) >= 2)
	{
		if (s[i][y] == '-' && s[i][y + 1] == 'n')
		{
			y++;
			while (s[i][y] == 'n')
				y++;
			if (y == (int)ft_strlen(s[i]))
				count++;
		}
		else
			return (count);
		i++;
		y = 0;
	}
	return (count);
}

int	ft_echo(char **s)
{
	int	y;
	int	i;

	s++;
	y = 0;
	i = flag_n(s);
	if (i > 0)
		y++;
	while (s[i])
	{
		printf("%s", s[i]);
		if (s[i + 1])
			printf(" ");
		i++;
	}
	if (y == 0)
		printf("\n");
	g_exit_code = 0;
	return (0);
}
