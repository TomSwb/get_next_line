/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomswb <tomswb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:56:31 by tomswb            #+#    #+#             */
/*   Updated: 2026/09/22 17:04:48 by tomswb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>

void	stdin_gnl(void);
void	one_file_gnl(char **av);
void	many_files_gnl(char **av);

int	main(int ac, char **av)
{
	if (ac == 1)
		stdin_gnl();
	else if (ac == 2)
		one_file_gnl(av);
	else
		many_files_gnl(av);
}

void	stdin_gnl(void)
{
	int		fd;
	char	*line;
	size_t	len;

	fd = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		len = find_c_index(line, '\0');
		write(1, line, len);
		free(line);
		line = get_next_line(fd);
	}
}

void	one_file_gnl(char **av)
{
	int		fd;
	char	*line;
	size_t	len;
	char	c;
	size_t i;

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

void	many_files_gnl(char **av)
{
	int *fds;
	char *line;
	char c;
	size_t len;
	size_t i;
	size_t line_len;
	
	fds = allocate_fds(av, &len);
	if (!fds)
		return ;
	i = 0;
	while (check_fds(fds, len) == 1)
	{
		i = 0;
		while (i < len)
		{
			if (fds[i] != -1)
			{
				line = get_next_line(fds[i]);
				if (line != NULL)
				{
					line_len = find_c_index(line, '\0');
					write(1, line, line_len);
					free(line);
					read(0, &c, 1);
					while (c != '\n')
						read(0, &c, 1);
				}
				else
				{
					close(fds[i]);
					fds[i] = -1;
				}
			}
			i++;
		}
	}
	free(fds);
}

int *allocate_fds(char **av, size_t *i)
{
	int *fds;
	
	*i = 1;
	while (av[*i])
		(*i)++;
	fds = malloc(sizeof(int) * *i);
	if (!fds)
		return (NULL);
	*i = 1;
	while (av[*i])
	{
		fds[(*i) - 1] = open(av[*i], O_RDONLY);
		(*i)++;
	}
	fds[(*i) - 1] = -1;
	return (fds);
}

int check_fds(int *fds, size_t len)
{
	size_t i;
	
	i = 0;
	while (i < len)
	{
		if (fds[i] != -1)
			return (1);
		i++;
	}
	return (0);
}
