************************************************************************** */

#include "minishell.h"

char	*cleanup_split(char **split_path)
{
	free_and_cleanup_split(split_path);
	return (NULL);
}
