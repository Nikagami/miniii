
#ifndef STRUCT_H
# define STRUCT_H
# include "define.h"

typedef struct s_token			t_token;
typedef struct s_command_execution			t_command_execution;
typedef struct s_env			t_environnement;
typedef struct s_commande_line	t_commande_line;

struct		s_env
{
	int		declare_status;
	char	*str;
	t_environnement	*next;
};


struct			s_token
{
	t_token_type	token_type;
	bool		expanded;
	char		*token_value;
	t_token		*next_t;
};

struct		s_command_execution
{
	int		output_fd;
	char	**argv;
	int		input_fd;
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
