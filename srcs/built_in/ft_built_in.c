
#include "minishell.h"

extern int	g_exit_code;

int	ft_sup_int(char *s)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	if (s[i] == '-')
	{
		i++;
		sign = -1;
	}
	while (s[i])
	{
		result = result * 10 + s[i] - '0';
		i++;
		if (result > 2147483648)
			return (2);
	}
	result = result * sign;
	if (result > 2147483647)
		return (2);
	return (0);
}

int	ft_non_int(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '-')
		i++;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
		{
			write(2, "minishell: exit: ", 17);
			write(2, s, ft_strlen(s));
			write(2, ": numeric argument required\n", 28);
			return (2);
		}
		i++;
	}
	return (ft_sup_int(s));
}

int	exit_bltin(char **args, t_commande_line **first, pid_t *pid)
{
	int	status_code;

	status_code = 0;
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
		status_code = ft_atoi(args[1]);
		if (args[2] != NULL)
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			g_exit_code = 1;
			return (2);
		}
		free_and_exit(first, pid, status_code);
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
