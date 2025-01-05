/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gestion_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:16:38 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:16:42 by trgaspar         ###   ########.fr       */
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
