/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:19:07 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:39:55 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "define.h"

typedef struct s_token				t_token;
typedef struct s_command_execution	t_command_execution;
typedef struct s_env				t_env;
typedef struct s_commande_line		t_commande_line;

struct		s_env
{
	int		declare_status;
	char	*str;
	t_env	*next;
};

struct			s_token
{
	t_token_t		token_type;
	bool			expanded;
	char			*t_value;
	t_token			*next_t;
};

struct		s_command_execution
{
	int					output_fd;
	char				**argv;
	int					input_fd;
	t_command_execution	*next;
};

struct				s_commande_line
{
	t_token			*first_token;
	char			**argv;
	char			*command_strings;
	char			**envp;
	int				input_fd;
	char			*file_name;
	int				output_fd;
	t_commande_line	*next_cmd;
};

#endif
