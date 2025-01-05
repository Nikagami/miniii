/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:29:12 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 10:29:15 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin(char *str)
{
	if (str == NULL)
		return (0);
	if (ft_strcmp("exit", str))
		return (2);
	if (ft_strcmp("cd", str))
		return (1);
	else if (ft_strcmp("echo", str))
		return (1);
	else if (ft_strcmp("env", str))
		return (1);
	else if (ft_strcmp("pwd", str))
		return (1);
	else if (ft_strcmp("export", str))
		return (1);
	else if (ft_strcmp("unset", str))
		return (1);
	return (0);
}
