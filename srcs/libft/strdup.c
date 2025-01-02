
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(sizeof(const char) * ft_strlen(s1) + 1);
	if (str == NULL)
		return (NULL);
	str[ft_strlen(s1)] = '\0';
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	return (str);
}
