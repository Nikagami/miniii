/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:06:42 by lchristo          #+#    #+#             */
/*   Updated: 2024/12/30 19:15:39 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "struct.h"

int			find_next_quote(char	*str, int i);

void		set_token_type(t_token *new);
void		reset_token(t_token *new);
int			check_builtin(char *str);

void		add_to_tail(t_commande_line **first, t_commande_line *add_back);
void		add_token_to_tail(t_token **first, t_token *add_back);
int			count_cmds(t_commande_line *cmd);

int			quote_not_pair(char	*str);
t_quote_state		manage_quote_state(char c, t_quote_state quote);
t_quote_state		complete_quote_update(t_token *stc, int *i, t_quote_state quote, char **s1);
int			parse_command_line(t_commande_line **cmd_lst, char *str);

int			is_delimiter(char c);
int			is_redir(char c);

int			handle_words_expand(t_commande_line **block);
int			handle_limitor(t_token *stc, char *str);
int			check_file_type(t_token_type type);
char		*expand_limitor(t_token *stc, char *str, int i);
char		*process_single_quoted_word(char *str, int *i, char *s1);
char		*process_double_quoted_word(char *str, int *i, char *s1);
char		*extract_before_env(char *str, char *s1, int *i, int j);
char		*process_unquoted_word(t_token **stc, char *str, int *i, char *s1);
char		*handle_env_var(char *str, char *tmp, int *i);
char		*unquote_and_cat(char *str, char *s1, int *i, int j);

int			syntax_error_file(t_token_type type);
int			check_file_type(t_token_type type);
int			update_token_string(char *str, t_token **stc, char *s1);
char		*initialize_string(char **str, char *duplica, int *cur, char **s1);
t_token_type	change_file_type(t_token_type type, int *file);
int			file_error_message(t_commande_line *cur_b);
t_token_type	change_type_file(t_token_type type, int *file);

char		*lookup_env_var(int *j, char *str);

char		*dup_fake_env(char *str);
char		*create_fake_env(int *j, int len_str);
int			get_fake_env_length(char *str);

int			free_all_cmds(t_commande_line **cmd_line);
void		free_strings(char *s1, char *s2);
int			free_cmd_and_ret_err(t_commande_line *str);
int			clean_token_and_rep_err(t_token *tok);
char		*free_and_nullify(char *s1);
void		free_and_cleanup_split(char **split);
char		*free_and_cleanup_split_token(char **split, t_token *tok);
int			free_array_and_ret_err(char *str);

char		*cleanup_split_and_ret_str(char **split, char *str);

int			cmd_line_process(char *string, t_commande_line **first);

int			tokenize_cmd_lines(t_commande_line **first);

int			prepare_cmd_args(t_commande_line **cmd);

int			ft_strncmp(char *str, char *to, int n);
void		fetch_env(char **env);

#endif
