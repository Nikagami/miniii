/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:58:15 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/31 17:47:37 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	display_export(void)
{
	t_environnement	**env;

	env = access_env();
	view_export(env);
}

int	check_export_syntax(char *s)
{
	int	i;

	i = 1;
	if ((ft_is_alpha(s[0]) && s[0] != '_'))
		return (1);
	while (s[i] && s[i] != '=')
	{
		if ((ft_is_alpha_num(s[i]) && s[i] != '_'))
		{
			if (!(s[i] == '+' && s[i + 1] == '='))
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export(char **s)
{
	int	i;

	i = 1;
	g_exit_code = 0;
	if (*(s + 1) == NULL)
	{
		display_export();
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

void	view_export(t_environnement **env)
{
	int		len;
	t_environnement	*current;

	current = *env;
	while (current)
	{
		len = key_len(current->str);
		if (current->declare_status == 1)
			printf("declare -x %.*s", len, current->str);
		else
			printf("export %.*s", len, current->str);
		if (len < (int)ft_strlen(current->str))
			printf("=\"%s\"", current->str + len + 1);
		printf("\n");
		current = current->next;
	}
}
