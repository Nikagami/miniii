/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:52:24 by viporten          #+#    #+#             */
/*   Updated: 2024/12/30 19:48:20 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "struct.h"

/* -------------------------------------------------------------------------- */
/*                     FILE = built_in/ft_built_in_pwd.c                      */
/* -------------------------------------------------------------------------- */
int		ft_pwd_bltn(char **str);
int		ft_pwd_fd(char **str, int fd);

/* -------------------------------------------------------------------------- */
/*                     FILE = built_in/ft_built_in_echo.c                     */
/* -------------------------------------------------------------------------- */
int		flag_n(char **str);
int		ft_echo(char **str);
int		ft_echo_fd(char **str, int fd);
void	display_env_fd(t_environnement **env, int fd);
int		env_fd(char **str, int fd);

/* -------------------------------------------------------------------------- */
/*                     FILE = built_in/ft_built_in_env.c                      */
/* -------------------------------------------------------------------------- */
int		process_env(char **str);
int		env_fd(char **str, int fd);
int		check_equal(char *str);
void	display_env(t_environnement **env);
void	display_env_fd(t_environnement **env, int fd);
char	*process_str(char *str);
char	*lookup_env(char *str);

/* -------------------------------------------------------------------------- */
/*                      FILE = built_in/ft_delete_key.c                       */
/* -------------------------------------------------------------------------- */
int		rm_env(char *str);
void	rm_env_call(t_environnement **env, char *key);

/* -------------------------------------------------------------------------- */
/*                    FILE = built_in/ft_environnement_singletone.c                     */
/* -------------------------------------------------------------------------- */
int		key_len(char *env);
int		handle_env_actions(char *str, t_environnement_action mode);

/* -------------------------------------------------------------------------- */
/*                       FILE = built_in/ft_built_in.c                        */
/* -------------------------------------------------------------------------- */
int		run_builtin(char *str, char **args,
			t_commande_line **first, pid_t *pid);

/* -------------------------------------------------------------------------- */
/*                       FILE = built_in/ft_add_value.c                       */
/* -------------------------------------------------------------------------- */
int		env_add(char *str);
int		new_env_value(t_environnement **env_list, char *env, int declare);

/* -------------------------------------------------------------------------- */
/*                      FILE = built_in/ft_built_in_cd.c                      */
/* -------------------------------------------------------------------------- */
int		ft_cd(char **str);
int		ft_cd_fd(char **str, int fd);

/* -------------------------------------------------------------------------- */
/*                      FILE = built_in/ft_push_front.c                       */
/* -------------------------------------------------------------------------- */
int		add_env_front(char *env, t_environnement **begin_lst, int declare);
int		run_builtin_fd(char *str, char **args,
			t_commande_line **first, pid_t *pid);

/* -------------------------------------------------------------------------- */
/*                    FILE = built_in/ft_built_in_export.c                    */
/* -------------------------------------------------------------------------- */
void	display_export(void);
void	display_export_fd(int fd);
int		ft_export(char **str);
int		ft_export_fd(char **str, int fd);
void	view_export(t_environnement **env);
int		ft_export_fd(char **str, int fd);
int		check_export_syntax(char *s);
char	*rm_plus(char *env);

/* -------------------------------------------------------------------------- */
/*                     FILE = built_in/ft_gestion_error.c                     */
/* -------------------------------------------------------------------------- */
int		display_error(char *str1, char *str2);

/* -------------------------------------------------------------------------- */
/*                       FILE = built_in/ft_init_environnement.c                        */
/* -------------------------------------------------------------------------- */
t_environnement	**access_env(void);
int		load_env(char **env);

/* -------------------------------------------------------------------------- */
/*                       FILE = built_in/ft_free_env.c                        */
/* -------------------------------------------------------------------------- */
void	free_env(void);
void	clear_envlist(t_environnement **env);
void	free_env_node(t_environnement *env);

/* -------------------------------------------------------------------------- */
/*                       FILE = built_in/ft_get_value.c                       */
/* -------------------------------------------------------------------------- */
char	*lookup_env(char *str);
char	*access_env_value(t_environnement **env, char *str);
char	*lookup_env_str(t_environnement **env, char *str);

/* -------------------------------------------------------------------------- */
/*                    FILE = built_in/ft_built_in_unset.c                     */
/* -------------------------------------------------------------------------- */
int		ft_unset(char **str);
int		ft_unset_fd(char **str, int fd);
int		has_equal(char *str);
int		free_and_exit(t_commande_line **first, pid_t *pid, int ret);

#endif
