/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gestion_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:02:06 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/31 17:54:53 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	display_error(char *str1, char *str2)
{
	char	*status_code;

	g_exit_code = 1;
	status_code = ft_strjoin(str1, str2);
	if (status_code == NULL)
		return (50);
	perror(status_code);
	free(status_code);
	return (0);
}
