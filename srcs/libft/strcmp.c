/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:45:17 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 10:45:20 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *str, char *in)
{
	int	len_str;
	int	len_in;
	int	i;

	i = 0;
	len_str = 0;
	len_in = 0;
	len_str = ft_strlen(str);
	len_in = ft_strlen(in);
	if (len_str != len_in)
		return (0);
	while (i < len_in)
	{
		if (str[i] != in[i])
			return (0);
		i++;
	}
	return (1);
}
