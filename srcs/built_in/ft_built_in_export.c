/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:58:15 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/30 19:25:38 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

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

int	ft_export(char **str)
{
	int	i;

	i = 1;
	g_exit_status = 0;
	if (*(str + 1) == NULL)
	{
		display_export();
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

void	view_export(t_environnement **env)
{
	t_environnement	*cur;
	int		len;

	cur = *env;
	while (cur)
	{
		len = key_len(cur->str);
		if (cur->declare_status == 1)
			printf("declare -x %.*s", len, cur->str);
		else
			printf("export %.*s", len, cur->str);
		if (len < (int)ft_strlen(cur->str))
			printf("=\"%s\"", cur->str + len + 1);
		printf("\n");
		cur = cur->next;
	}
}
