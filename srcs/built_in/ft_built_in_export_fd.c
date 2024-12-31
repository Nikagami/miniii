/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_export_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:58:15 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/31 17:46:20 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	ft_export_fd(char **s, int fd)
{
	int	i;

	i = 1;
	g_exit_code = 0;
	if (*(s + 1) == NULL)
	{
		display_export_fd(fd);
		return (0);
	}
	while (s[i] != NULL)
	{
		if (check_export_syntax(s[i]))
		{
			g_exit_code = 1;
			printf("minishell: export: '%s': not a valid identifier\n", s[i]);
		}
		else if (handle_env_actions(s[i], ENV_ADD) == 50)
			return (50);
		i++;
	}
	return (0);
}

void	ft_show_export_fd(t_environnement **env, int fd)
{
	t_environnement	*current;
	int		len;

	current = *env;
	while (current)
	{
		len = key_len(current->str);
		if (current->declare_status == 1)
			ft_putstr_fd("declare -x ", fd);
		else
			ft_putstr_fd("export ", fd);
		ft_putstr_minus_fd(current->str, len, fd);
		if (len < (int)ft_strlen(current->str))
		{
			ft_putchar_fd('=', fd);
			ft_putchar_fd('"', fd);
			ft_putstr_fd(current->str + len + 1, fd);
			ft_putchar_fd('"', fd);
		}
		ft_putchar_fd('\n', fd);
		current = current->next;
	}
}

void	display_export_fd(int fd)
{
	t_environnement	**env;

	env = access_env();
	ft_show_export_fd(env, fd);
}
