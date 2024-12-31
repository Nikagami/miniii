/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:26:17 by laclide           #+#    #+#             */
/*   Updated: 2024/12/31 18:12:39 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*process_non_env(char *s, char *s1, int *current)
{
	char	*new;
	char	*join;
	int		start;

	start = *current;
	while (s[*current] && s[*current] != '$')
		(*current)++;
	new = malloc(sizeof(char) * ((*current) - start));
	if (new == NULL)
		return (free_and_nullify(s1));
	new = ft_strncpy(new, s + start, ((*current) - start));
	join = ft_strjoin(s1, new);
	free_strings(s1, new);
	return (join);
}

static char	*if_env(char *s, char *s1, int *current)
{
	char	*env;
	char	*join;

	env = handle_env_var(s, s1, current);
	if (env == NULL)
		return (free_and_nullify(s1));
	join = ft_strjoin(s1, env);
	free_strings(s1, env);
	return (join);
}

static char	*expanded_str(char *s)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (s[i])
	{
		if (s[i] == '$')
		{
			new = if_env(s, new, &i);
			if (new == NULL)
				return (NULL);
		}
		else
		{
			new = process_non_env(s, new, &i);
			if (new == NULL)
				return (NULL);
		}
	}
	free(s);
	return (new);
}

int	write_in_fd(int fd, char *limitor, bool expanded)
{
	char	*s;

	while (1)
	{
		s = readline(">");
		if (s == NULL)
			return (45);
		if (ft_strcmp(limitor, s) == 1)
			break ;
		if (s[0] != '\0')
		{
			if (expanded == 0)
			{
				s = expanded_str(s);
				if (s == NULL)
					return (50);
			}
		}
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
		free(s);
	}
	free(s);
	return (0);
}

int	setup_heredoc_fd(t_commande_line **c_list, t_token **current)
{
	char	*file_name;
	int		fd;

	file_name = NULL;
	fd = -1;
	while (fd == -1)
	{
		if (file_name)
			free(file_name);
		file_name = random_name_generator();
		fd = open(file_name, O_CREAT | O_EXCL | O_RDWR, 0644);
	}
	write_in_fd(fd, (*current)->token_value, (*current)->expanded);
	fd = open(file_name, O_RDONLY);
	(*c_list)->input_fd = fd;
	if ((*c_list)->file_name != NULL)
	{
		unlink((*c_list)->file_name);
		free((*c_list)->file_name);
	}
	(*c_list)->file_name = file_name;
	return (fd);
}
