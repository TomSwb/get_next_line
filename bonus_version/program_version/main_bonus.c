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
void	many_files_gnl(char **av);

int	main(int ac, char **av)
{
	if (ac == 1)
		stdin_gnl();
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

void	many_files_gnl(char **av)
{
	int *fds;
	size_t len;
	size_t i;
	
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

void process_fd_line(int *fds, size_t i)
{
	char *line;
	char c;
	size_t line_len;
	
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
}