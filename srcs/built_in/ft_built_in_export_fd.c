/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_export_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:58:15 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/30 19:25:38 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	ft_export_fd(char **str, int fd)
{
	int	i;

	i = 1;
	g_exit_status = 0;
	if (*(str + 1) == NULL)
	{
		display_export_fd(fd);
		return (0);
	}
	while (str[i] != NULL)
	{
		if (check_export_syntax(str[i]))
		{
			g_exit_status = 1;
			printf("minishell: export: '%s': not a valid identifier\n", str[i]);
		}
		else if (handle_env_actions(str[i], ENV_ADD) == 50)
			return (50);
		i++;
	}
	return (0);
}

void	ft_show_export_fd(t_environnement **env, int fd)
{
	t_environnement	*cur;
	int		len;

	cur = *env;
	while (cur)
	{
		len = key_len(cur->str);
		if (cur->declare_status == 1)
			ft_putstr_fd("declare -x ", fd);
		else
			ft_putstr_fd("export ", fd);
		ft_putstr_minus_fd(cur->str, len, fd);
		if (len < (int)ft_strlen(cur->str))
		{
			ft_putchar_fd('=', fd);
			ft_putchar_fd('"', fd);
			ft_putstr_fd(cur->str + len + 1, fd);
			ft_putchar_fd('"', fd);
		}
		ft_putchar_fd('\n', fd);
		cur = cur->next;
	}
}

void	display_export_fd(int fd)
{
	t_environnement	**env;

	env = access_env();
	ft_show_export_fd(env, fd);
}
