/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:18:43 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:37:57 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

typedef enum e_quote_state
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	BACKSLASH,
	QUOTE_END
}	t_quote;

typedef enum e_env_action
{
	ENV_GET,
	ENV_DELETE,
	ENV_FREE,
	ENV_ADD
}			t_env_action;

typedef enum e_token_type
{
	TOKEN_NONE,
	TOKEN_ARG,
	TOKEN_BUILTIN,
	TOKEN_OPEN_FILE,
	TOKEN_HERE_DOC,
	TOKEN_LIMITOR,
	TOKEN_CREAT_FILE,
	TOKEN_WRITE_FILE,
	TOKEN_FILE_IN,
	TOKEN_FILE_OUT,
	TOKEN_FILE_OUT_APPEND,
	TOKEN_ENDS
}				t_token_t;

#endif