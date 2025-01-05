/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:45:30 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 10:45:33 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(const char) * ft_strlen(s1) + 1);
	if (str == NULL)
		return (NULL);
	str[ft_strlen(s1)] = '\0';
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	return (str);
}
