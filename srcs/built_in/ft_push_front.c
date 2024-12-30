/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:30:18 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/30 19:25:38 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_env_front(char *env, t_environnement **begin_lst, int declare)
{
	t_environnement	*env_new;

	env_new = malloc(sizeof(t_environnement));
	if (env_new == NULL)
		return (50);
	env_new->str = rm_plus(env);
	env_new->declare_status = declare;
	if (env_new->str == NULL)
		return (50);
	env_new->next = *begin_lst;
	*begin_lst = env_new;
	return (0);
}
