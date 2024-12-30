/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:26:17 by laclide           #+#    #+#             */
/*   Updated: 2024/12/30 19:23:41 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*if_no_env(char *str, char *s1, int *cur)
{
	char	*new;
	char	*join;
	int		start;

	start = *cur;
	while (str[*cur] && str[*cur] != '$')
		(*cur)++;
	new = malloc(sizeof(char) * ((*cur) - start));
	if (new == NULL)
		return (free_and_nullify(s1));
	new = ft_strncpy(new, str + start, ((*cur) - start));
	join = ft_strjoin(s1, new);
	free_strings(s1, new);
	return (join);
}

static char	*if_env(char *str, char *s1, int *cur)
{
	char	*env;
	char	*join;

	env = handle_env_var(str, s1, cur);
	if (env == NULL)
		return (free_and_nullify(s1));
	join = ft_strjoin(s1, env);
	free_strings(s1, env);
	return (join);
}

static char	*expanded_str(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			new = if_env(str, new, &i);
			if (new == NULL)
				return (NULL);
		}
		else
		{
			new = if_no_env(str, new, &i);
			if (new == NULL)
				return (NULL);
		}
	}
	free(str);
	return (new);
}

int	write_in_fd(int fd, char *limitor, bool expanded)
{
	char	*str;

	while (1)
	{
		str = readline(">");
		if (str == NULL)
			return (45);
		if (ft_strcmp(limitor, str) == 1)
			break ;
		if (str[0] != '\0')
		{
			if (expanded == 0)
			{
				str = expanded_str(str);
				if (str == NULL)
					return (50);
			}
		}
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	free(str);
	return (0);
}

int	setup_heredoc_fd(t_commande_line **cmdl, t_token **cur)
{
	int		fd;
	char	*name_file;

	name_file = NULL;
	fd = -1;
	while (fd == -1)
	{
		if (name_file)
			free(name_file);
		name_file = random_name_generator();
		fd = open(name_file, O_CREAT | O_EXCL | O_RDWR, 0644);
	}
	write_in_fd(fd, (*cur)->token_value, (*cur)->expanded);
	fd = open(name_file, O_RDONLY);
	(*cmdl)->input_fd = fd;
	if ((*cmdl)->file_name != NULL)
	{
		unlink((*cmdl)->file_name);
		free((*cmdl)->file_name);
	}
	(*cmdl)->file_name = name_file;
	return (fd);
}
