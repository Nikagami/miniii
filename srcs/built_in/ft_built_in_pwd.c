
#include "minishell.h"

extern int	g_exit_code;

int		ft_pwd_bltn(char **s)
{
	char	*pwd;

	if (*s == NULL)
		return (0);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (50);
	g_exit_code = 0;
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
