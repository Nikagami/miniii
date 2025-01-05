/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:15:52 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:26:09 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

char	*write_bad_cmd_free_split(char *s, char **path_parts)
{
	free_and_cleanup_split(path_parts);
	write_all_consecutif("minishell: ", s, " command not found\n");
	return (NULL);
}

char	*write_bad_cmd_free(char *s)
{
	write_all_consecutif("minishell: ", s, "command not found\n");
	free(s);
	return (NULL);
}

char	*build_path(char *s, char *path)
{
	char	*back_slash;
	char	*full_path;

	back_slash = ft_strjoin(path, "/");
	if (back_slash == NULL)
		return (NULL);
	full_path = ft_strjoin(back_slash, s);
	free(back_slash);
	if (full_path == NULL)
		return (NULL);
	return (full_path);
}

int	can_access(char *s, char *path)
{
	char	*full_path;

	full_path = build_path(s, path);
	if (full_path == NULL)
		return (50);
	if (access(full_path, X_OK) == 0)
	{
		free(full_path);
		return (1);
	}
	free(full_path);
	return (0);
}

char	*get_executable_path(char *s, char *path, int i)
{
	int		status_code;
	char	**path_parts;
	char	*full_path;

	if (s && (s[0] == '.' || s[0] == '/'))
		return (s);
	path_parts = ft_strsplit(path, ':');
	if (path_parts == NULL)
		return (write_bad_cmd_free(s));
	while (path_parts[i] && s[0] != '\0')
	{
		status_code = can_access(s, path_parts[i]);
		if (status_code == 1)
		{
			full_path = build_path(s, path_parts[i]);
			free_and_cleanup_split(path_parts);
			return (full_path);
		}
		if (status_code == 50)
			return (cleanup_split(path_parts));
		i++;
	}
	write_bad_cmd_free_split(s, path_parts);
	g_exit_code = 127;
	return (s);
}
