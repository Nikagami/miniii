
#include "minishell.h"

extern int	g_exit_code;

int	ft_pwd_fd(char **s, int fd)
{
	char	*pwd;

	if (*s == NULL)
		return (0);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (50);
	g_exit_code = 0;
	ft_putstr_fd(pwd, fd);
	ft_putchar_fd('\n', fd);
	free(pwd);
	return (0);
}
