/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 08:58:02 by laclide           #+#    #+#             */
/*   Updated: 2024/12/31 15:25:30 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_exit_code;

int	pars(char *str, t_commande_line **cmd_line)
{
	int	res;

	res = quote_not_pair(str);
	if (res > 0)
	{
		write(2, "minishell: miss quote\n", 22);
		free_all_cmds(cmd_line);
	}
	else
	{
		if (cmd_line_process(str, cmd_line) > 0)
			return (cleanup_on_malloc_fail(cmd_line, str));
		if (tokenize_cmd_lines(cmd_line) > 0)
			return (cleanup_on_malloc_fail(cmd_line, str));
		res = handle_words_expand(cmd_line);
		if (res != 0)
		{
			free_all_cmds(cmd_line);
			if (res == 50)
				return (free_array_and_ret_err(str));
		}
		if (prepare_cmd_args(cmd_line) != 0)
			return (cleanup_on_malloc_fail(cmd_line, str));
	}
	return (res);
}

void	handle_cmd_signal(int sig)
{
	g_exit_code += sig;
	if (sig == 2)
	{
		g_exit_code = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", ft_strlen("Quit (core dumped)\n"));
		exit (1);
	}
}

int	check_str(char *str)
{
	int	i;
	int	dif;

	i = 0;
	dif = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '|')
			dif = 1;
		if (str[i] == '|')
		{
			if (dif == 0)
				return (1);
			dif = 0;
		}
		i++;
	}
	return (0);
}

void	go_to_exec(t_commande_line **cmd_line, char *str)
{
	int	res;

	res = pars(str, cmd_line);
	if (res == 50)
	{
		free_resources_on_malloc_error(cmd_line, str);
		exit (1);
	}
	if (res == 0)
	{
		if (str != NULL && *cmd_line != NULL)
		{
			res = run_commands(cmd_line);
			if (res != 0)
			{
				process_error_and_cleanup(cmd_line, str, res);
				exit (1);
			}
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	char			*str;
	t_commande_line	*cmd_line;

	cmd_line = NULL;
	g_exit_code = 0;
	load_env(envp);
	signal(SIGINT, handle_cmd_signal);
	signal(SIGQUIT, SIG_IGN);
	if (!ac && !av)
		return (0);
	while (1)
	{
		str = readline("minishell$> ");
		add_history(str);
		signal(SIGINT, handle_cmd_signal);
		signal(SIGQUIT, SIG_IGN);
		if (str == NULL)
			return (exit_with_cleanup(&cmd_line));
		if (check_str(str) != 0)
			syntax_error_message();
		else
			go_to_exec(&cmd_line, str);
		free_cmd_and_str(&cmd_line, str);
	}
}
