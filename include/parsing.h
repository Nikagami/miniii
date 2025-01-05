/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:48:56 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:42:55 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "struct.h"

void		set_token_t(t_token *new);
void		reset_token(t_token *new);
int			check_builtin(char *str);

void		lst_add_back(t_commande_line **first, t_commande_line *add_back);
void		add_token_to_tail(t_token **first, t_token *add_back);
int			count_cmds(t_commande_line *cmd);

int			quote_not_pair(char	*str);
t_quote		manage_quote_state(char c, t_quote quote);
t_quote		end_quote_update(t_token *stc, int *i, t_quote quote, char **s1);

int			is_delimiter(char c);
int			is_redir(char c);

int			handle_words_expand(t_commande_line **block);
int			handle_limitor(t_token *stc, char *str);
int			check_file_type(t_token_t type);
char		*expand_limitor(t_token *stc, char *str, int i);
char		*process_single_quoted_word(char *str, int *i, char *s1);
char		*process_double_quoted_word(char *str, int *i, char *s1);
char		*extract_before_env(char *str, char *s1, int *i, int j);
char		*process_unquoted_word(t_token **stc, char *str, int *i, char *s1);
char		*handle_env_var(char *str, char *tmp, int *i);
char		*unquote_and_cat(char *str, char *s1, int *i, int j);

int			syntax_error_file(t_token_t type);
int			check_file_type(t_token_t type);
int			update_token_string(char *str, t_token **stc, char *s1);
char		*initialize_string(char **str, char *duplica, int *cur, char **s1);
t_token_t	change_file_type(t_token_t type, int *file);
int			file_error_message(t_commande_line *cur_b);
t_token_t	change_type_file(t_token_t type, int *file);

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

#endif
