/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomswb <tomswb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:56:40 by tomswb            #+#    #+#             */
/*   Updated: 2026/09/19 15:56:41 by tomswb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include 'get_next_line.h'

char	*ft_extract_buffer(int fd, ssize_t *reading)
{
	char		*line;

	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	*reading = read(fd, line, BUFFER_SIZE);
	if (*reading == -1)
	{
		free(line);
		return (NULL);
	}
	line[*reading] = '\0';
	return (line);
}