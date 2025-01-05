/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:15:20 by trgaspar          #+#    #+#             */
/*   Updated: 2025/01/05 11:15:22 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	aleatori_char(void)
{
	int		fd;
	int		n;
	char	buff[4];

	fd = open("/dev/random", O_RDONLY);
	if (fd < -1)
		return (-1);
	read(fd, buff, 4);
	n = *(int *)buff;
	if (n < 0)
		n++;
	if (n < 0)
		n = n * (-1);
	close(fd);
	return ('a' + n % 26);
}

char	*random_name_generator(void)
{
	int		i;
	char	*file_name;

	i = 0;
	file_name = malloc(sizeof(char) * 11);
	file_name[10] = '\0';
	while (i < 10)
	{
		file_name[i] = (char)aleatori_char();
		i++;
	}
	return (file_name);
}
