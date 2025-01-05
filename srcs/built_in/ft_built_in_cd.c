/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:17:52 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:33:51 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	has_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_get_home(void)
{
	int		len;
	t_env	*copy;

	len = key_len("HOME=");
	copy = *access_env();
	while (copy)
	{
		if (len == key_len(copy->str)
			&& !ft_strncmp(copy->str, "HOME", len))
		{
			if (has_equal(copy->str))
				return (copy->str + len + 1);
			return (NULL);
		}
		copy = copy->next;
	}
	return (NULL);
}

int	ft_pwd(char *s)
{
	char	*pwd;
	int		status_code;
	char	*oldpwd;

	status_code = 0;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		free(pwd);
		return (50);
	}
	oldpwd = ft_strjoin(s, pwd);
	free(pwd);
	if (oldpwd == NULL)
	{
		free(oldpwd);
		return (50);
	}
	status_code = env_add(oldpwd);
	free(oldpwd);
	return (status_code);
}

int	ft_cd(char **str)
{
	if (*(str + 1) == NULL || ft_strcmp(str[1], "~"))
	{
		*(str + 1) = ft_get_home();
		if (*(str + 1) == NULL)
		{
			printf("HOME not set\n");
			return (0);
		}
		if (str[1][0] == '\0')
			return (0);
	}
	if (ft_pwd("OLDPWD=") == 50)
		return (50);
	if (chdir(*(str + 1)) == -1)
		if (display_error("minishell: cd: ", *(str + 1)) == 50)
			return (50);
	if (ft_pwd("PWD=") == 50)
		return (50);
	return (0);
}
