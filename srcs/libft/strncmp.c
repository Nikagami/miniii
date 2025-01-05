/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:45:45 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 10:45:48 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *str, char *to, int n)
{
	int	i;

	i = 0;
	if (str == NULL || to == NULL)
		return (-1);
	if ((int)ft_strlen(str) < n || (int)ft_strlen(to) < n)
		return (-1);
	while (i < n)
	{
		if (!str[i] || !to[i] || str[i] != to[i])
			return (str[i] - to[i]);
		i++;
	}
	return (0);
}
