/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomswb <tomswb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:56:37 by tomswb            #+#    #+#             */
/*   Updated: 2026/09/19 20:00:55 by tomswb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_next_line(int fd)
{
	char		*line;
	static char	*lftvr; 
	size_t		len;
	int			reading;

	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	reading = read(fd, line, BUFFER_SIZE);
	if (reading == -1)
	{
		free(line);
		return (NULL);
	}
	line[reading + 1] = '\0';
	return (line);
}