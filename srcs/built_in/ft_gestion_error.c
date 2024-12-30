/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gestion_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:02:06 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/30 16:18:17 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	display_error(char *str1, char *str2)
{
	char	*ret;

	g_exit_status = 1;
	ret = ft_strjoin(str1, str2);
	if (ret == NULL)
		return (50);
	perror(ret);
	free(ret);
	return (0);
}
