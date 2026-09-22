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

char	*get_next_line(int fd)
{
	static char	*data;
	char		*line;
	ssize_t		reading;

	while (data == NULL || !ft_strchr(data, '\n'))
	{
		reading = ft_extract_buffer(fd, &data);
		if (reading < 0)
		{
			free(data);
			data = NULL;
			return (NULL);
		}
		if (reading == 0)
			break;
	}
	if (data == NULL)
		return (NULL);
	if (ft_extract_line(&line, &data))
	{
		free(data);
		data = NULL;
		return (NULL);
	}
	return (line);
}
