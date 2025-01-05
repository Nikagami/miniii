/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:45:02 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 10:45:05 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memset(void *b, int c, size_t len)
{
	char	*start;

	if (b == NULL)
		return (NULL);
	start = b;
	while (len)
	{
		*start = c;
		start++;
		len--;
	}
	return (b);
}
