
#ifndef EXEC_H
# define EXEC_H

# include "struct.h"

/* -------------------------------------------------------------------------- */
/*                           FILE = exec/ft_exist.c                           */
/* -------------------------------------------------------------------------- */
char	*build_path(char *str, char *path);
int		can_access(char *str, char *path);
char	*get_executable_path(char *str, char *path, int i);

/* -------------------------------------------------------------------------- */
/*                        FILE = exec/ft_lst_to_str.c                         */
/* -------------------------------------------------------------------------- */
int		env_len(void);
char	**envlist_to_array(t_environnement **envp);

/* -------------------------------------------------------------------------- */
/*                           FILE = exec/fill_fd.c                            */
/* -------------------------------------------------------------------------- */
int		set_fd(t_commande_line **stc);

/* -------------------------------------------------------------------------- */
/*                           FILE = exec/ft_exec.c                            */
/* -------------------------------------------------------------------------- */
int		run_commands(t_commande_line	**s_cmd_line);

int		initialize_pipes(t_commande_line **cmdl);
void	cleanup_fds(t_commande_line **cmdl);
int		handle_redirections(t_commande_line **cmdl);
char	**env_to_array(t_environnement **envp);

int		setup_heredoc_fd(t_commande_line **cmdl, t_token **cur);
char	*random_name_generator(void);

void	cleanup_and_exit(t_commande_line **first);
void	free_resources_and_exit(char **str,
			t_commande_line **first);
void	exit_on_error(char **str);
void	cleanup_all_and_exit(t_commande_line **cmd,
			pid_t *pid, char **str);
void	rm_and_free_file(char *file_name);

int		wait_for_process(t_commande_line **cmdl, pid_t *pid);
int		run_without_fork(t_commande_line **cmdl, pid_t *pid);
int		process_builtin(char **str, t_commande_line **cmdl,
			t_commande_line **first, pid_t *pid);
void	handle_signal(int sig);
char	*cleanup_split(char **split_path);

#endif
