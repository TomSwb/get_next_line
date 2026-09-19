/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomswb <tomswb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:56:31 by tomswb            #+#    #+#             */
/*   Updated: 2026/09/19 17:09:46 by tomswb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stddef.h>

static size_t	ft_strlen(char *s);

int	main(int ac, char **av)
{
	int		fd;
	char	*line;
	size_t	len;
	char	c;

	if (ac != 2)
		return (-1);
	else
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			return (-1);
		line = get_next_line(fd);
		while (line != NULL)
		{
			len = ft_strlen(line);
			write(1, line, len);
			free(line);
			read(0, &c, 1);
			while (c != '\n')
				read(0, &c, 1);
			line = get_next_line(fd);
		}
		close(fd);
	}
}

static size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
