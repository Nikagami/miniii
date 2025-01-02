
#include "minishell.h"

char	*initialize_string(char **str, char *duplica, int *cur, char **s1)
{
	*s1 = NULL;
	*cur = 0;
	*str = ft_strdup(duplica);
	free(duplica);
	if (*str == NULL)
		return (NULL);
	return (*str);
}

int	update_token_string(char *str, t_token **stc, char *s1)
{
	free(str);
	(*stc)->token_value = s1;
	return (0);
}

int	check_file_type(t_token_type type)
{
	if (type == TOKEN_CREAT_FILE || type == TOKEN_WRITE_FILE
		|| type == TOKEN_OPEN_FILE || type == TOKEN_HERE_DOC)
		return (1);
	return (0);
}

int	syntax_error_file(t_token_type type)
{
	write(2, "minishell: erreur de syntaxe",
		ft_strlen("minishell: erreur de syntaxe"));
	if (type == TOKEN_NONE)
		write(2, " newline\n", 9);
	if (type == TOKEN_CREAT_FILE)
		write(2, " >\n", 3);
	else if (type == TOKEN_WRITE_FILE)
		write(2, " >>\n", 4);
	else if (type == TOKEN_OPEN_FILE)
		write(2, " <\n", 3);
	else if (type == TOKEN_HERE_DOC)
		write(2, " <<\n", 4);
	return (12);
}

t_token_type	change_file_type(t_token_type type, int *file)
{
	*file = 1;
	return (type);
}
