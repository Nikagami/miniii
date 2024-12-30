/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:21:20 by laclide           #+#    #+#             */
/*   Updated: 2024/12/30 19:48:20 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	ft_sup_int(char *str)
{
	long	res;
	int		sig;
	int		i;

	res = 0;
	sig = 1;
	i = 0;
	if (str[i] == '-')
	{
		i++;
		sig = -1;
	}
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
		if (res > 2147483648)
			return (2);
	}
	res = res * sig;
	if (res > 2147483647)
		return (2);
	return (0);
}

int	ft_non_int(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			write(2, "minishell: exit: ", 17);
			write(2, str, ft_strlen(str));
			write(2, ": numeric argument required\n", 28);
			return (2);
		}
		i++;
	}
	return (ft_sup_int(str));
}

int	exit_bltin(char **args, t_commande_line **first, pid_t *pid)
{
	int	ret;

	ret = 0;
	printf("exit\n");
	if (args[1] != NULL)
	{
		if (ft_non_int(args[1]))
		{
			free_env();
			free_all_cmds(first);
			free(pid);
			exit (2);
		}
		ret = ft_atoi(args[1]);
		if (args[2] != NULL)
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			g_exit_status = 1;
			return (2);
		}
		free_and_exit(first, pid, ret);
	}
	return (free_and_exit(first, pid, 0));
}

int	run_builtin(char *str, char **args, t_commande_line **first, pid_t *pid)
{
	if (str == NULL)
		return (0);
	if (ft_strcmp("exit", str))
	{
		exit_bltin(args, first, pid);
		return (free_and_exit(first, pid, 1));
	}
	if (ft_strcmp("cd", str))
		ft_cd(args);
	else if (ft_strcmp("echo", str))
		ft_echo(args);
	else if (ft_strcmp("env", str))
		process_env(args);
	else if (ft_strcmp("pwd", str))
		ft_pwd_bltn(args);
	else if (ft_strcmp("export", str))
		ft_export(args);
	else if (ft_strcmp("unset", str))
		ft_unset(args);
	free(pid);
	free_env();
	free_all_cmds(first);
	return (0);
}

int	run_builtin_fd(char *str, char **args, t_commande_line **first, pid_t *pid)
{
	if (str == NULL)
		return (0);
	if (ft_strcmp("exit", str))
	{
		exit_bltin(args, first, pid);
		return (1);
	}
	if (ft_strcmp("cd", str))
		ft_cd(args);
	else if (ft_strcmp("echo", str))
		ft_echo_fd(args, (*first)->output_fd);
	else if (ft_strcmp("env", str))
		env_fd(args, (*first)->output_fd);
	else if (ft_strcmp("pwd", str))
		ft_pwd_fd(args, (*first)->output_fd);
	else if (ft_strcmp("export", str))
		ft_export_fd(args, (*first)->output_fd);
	else if (ft_strcmp("unset", str))
		ft_unset(args);
	return (0);
}
