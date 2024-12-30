/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:41:26 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/30 19:04:31 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

char	*write_bad_cmd_free_split(char *str, char **split_path)
{
	free_and_cleanup_split(split_path);
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, " : commande introuvable\n",
		ft_strlen(" : commande introuvable\n"));
	return (NULL);
}

char	*write_bad_cmd_free(char *str)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, " : commande introuvable\n",
		ft_strlen(" : commande introuvable\n"));
	free(str);
	return (NULL);
}

char	*build_path(char *str, char *path)
{
	char	*back_slash;
	char	*new;

	back_slash = ft_strjoin(path, "/");
	if (back_slash == NULL)
		return (NULL);
	new = ft_strjoin(back_slash, str);
	free(back_slash);
	if (new == NULL)
		return (NULL);
	return (new);
}

int	can_access(char *str, char *path)
{
	char	*try;

	try = build_path(str, path);
	if (try == NULL)
		return (50);
	if (access(try, X_OK) == 0)
	{
		free(try);
		return (1);
	}
	free(try);
	return (0);
}

char	*get_executable_path(char *str, char *path, int i)
{
	int		ret;
	char	**split_path;
	char	*try;

	if (str && (str[0] == '.' || str[0] == '/'))
		return (str);
	split_path = ft_strsplit(path, ':');
	if (split_path == NULL)
		return (write_bad_cmd_free(str));
	while (split_path[i] && str[0] != '\0')
	{
		ret = can_access(str, split_path[i]);
		if (ret == 1)
		{
			try = build_path(str, split_path[i]);
			free_and_cleanup_split(split_path);
			return (try);
		}
		if (ret == 50)
			return (cleanup_split(split_path));
		i++;
	}
	write_bad_cmd_free_split(str, split_path);
	g_exit_status = 127;
	return (str);
}
