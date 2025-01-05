/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:17:12 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:17:16 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	ft_pwd_bltn(char **s)
{
	char	*pwd;

	if (*s == NULL)
		return (0);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (50);
	g_exit_code = 0;
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
