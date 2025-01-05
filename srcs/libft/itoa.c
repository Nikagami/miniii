/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:44:46 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 10:44:50 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_int(int nbr, int *sign)
{
	int	i;

	*sign = 1;
	i = 1;
	if (nbr < 0)
	{
		*sign = -1;
		i++;
	}
	while (nbr >= 10)
	{
		i++;
		nbr = nbr / 10;
	}
	return (i);
}

void	fill_new(char *new, int sign, int nbr, int j)
{
	long	cp;
	int		divid;

	cp = nbr * sign;
	divid = 1000000000;
	while (divid > cp)
		divid = divid / 10;
	while (divid >= 10)
	{
		new[j] = cp / divid + '0';
		j++;
		cp = cp % divid;
		divid = divid / 10;
	}
	new[j] = cp + '0';
	new[j + 1] = '\0';
}

char	*ft_itoa(int nbr)
{
	int		sign;
	char	*new;
	int		j;

	j = 0;
	new = ft_memalloc(len_int(nbr, &sign));
	if (new == NULL)
		return (NULL);
	if (sign == -1)
	{
		new[0] = '-';
		j++;
	}
	fill_new(new, sign, nbr, j);
	return (new);
}
