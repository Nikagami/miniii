/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:15:31 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:31:57 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_array(t_env **envp)
{
	char	**env_array;
	t_env	*current;
	int		i;

	i = 0;
	current = *envp;
	while (current)
	{
		current = current->next;
		i++;
	}
	env_array = malloc(sizeof(char *) * (i + 1));
	env_array[i] = NULL;
	current = *envp;
	i = 0;
	while (current)
	{
		env_array[i] = current->str;
		i++;
		current = current->next;
	}
	return (env_array);
}

void	write_all_consecutif(char *s1, char *s2, char *s3)
{
	char	*msg;
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	msg = ft_strjoin(tmp, s3);
	free(tmp);
	ft_putstr_fd(msg, 2);
	free(msg);
}
