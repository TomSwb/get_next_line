/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomswb <tomswb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:56:31 by tomswb            #+#    #+#             */
/*   Updated: 2026/09/26 12:12:08 by tomswb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>

void	stdin_gnl(void);
void	files_gnl(char **av);
int		*allocate_fds(char **av, size_t *i);
int		check_fds(int *fds, size_t len);
void	process_fd_line(int *fds, size_t i);

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

void	files_gnl(char **av)
{
	int		*fds;
	size_t	len;
	size_t	i;

	fds = allocate_fds(av, &len);
	if (!fds)
		return ;
	i = 0;
	while (check_fds(fds, len) == 1)
	{
		i = 0;
		while (i < len)
		{
			process_fd_line(fds, i);
			i++;
		}
	}
	free(fds);
}

int	*allocate_fds(char **av, size_t *i)
{
	int	*fds;

	*i = 1;
	while (av[*i])
		(*i)++;
	fds = malloc(sizeof(int) * *i + 1);
	if (!fds)
		return (NULL);
	fds[0] = 0;
	*i = 1;
	while (av[*i])
	{
		fds[*i] = open(av[*i], O_RDONLY);
		(*i)++;
	}
	fds[*i] = -1;
	return (fds);
}

int	check_fds(int *fds, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (fds[i] != -1)
			return (1);
		i++;
	}
	return (0);
}

void	process_fd_line(int *fds, size_t i)
{
	char	*line;
	char	c;
	size_t	line_len;

	if (fds[i] != -1)
	{
		line = get_next_line(fds[i]);
		if (line != NULL)
		{
			c = fds[i] + 48;
			line_len = find_c_index(line, '\0');
			write(1, "Fd ", 3);
			write(1, &c, 1);
			write(1, " = ", 3);
			write(1, line, line_len);
			write(1, "\n", 1);
			free(line);
		}
		else
		{
			close(fds[i]);
			fds[i] = -1;
		}
	}
}
