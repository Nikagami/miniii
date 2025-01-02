#include "minishell.h"

extern int	g_exit_code;

int	ft_echo_fd(char **s, int fd)
{
	int	y;
	int	i;

	s++;
	y = 0;
	i = flag_n(s);
	if (i > 0)
		y++;
	while (s[i])
	{
		ft_putstr_fd(s[i], fd);
		if (s[i + 1])
			ft_putchar_fd(' ', fd);
		i++;
	}
	if (y == 0)
		ft_putchar_fd('\n', fd);
	g_exit_code = 0;
	return (0);
}
