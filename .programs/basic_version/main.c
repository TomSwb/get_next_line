/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomswb <tomswb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:56:31 by tomswb            #+#    #+#             */
/*   Updated: 2026/09/24 19:28:07 by tomswb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

void	ft_stdin_gnl(void);
void	ft_stdfile_gnl(char **av);

int	main(int ac, char **av)
{
	if (ac > 2)
		return (-1);
	if (ac == 1)
		ft_stdin_gnl();
	else
		ft_stdfile_gnl(av);
}

void	ft_stdin_gnl(void)
{
	int		fd;
	char	*line;
	size_t	len;

	fd = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		len = find_c_index(line, '\0');
		write(0, line, len);
		free(line);
		line = get_next_line(fd);
	}
}

void	ft_stdfile_gnl(char **av)
{
	int		fd;
	char	*line;
	size_t	len;
	char	c;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line != NULL)
	{
		len = find_c_index(line, '\0');
		write(1, line, len);
		free(line);
		read(0, &c, 1);
		while (c != '\n')
			read(0, &c, 1);
		line = get_next_line(fd);
	}
	close(fd);
}
