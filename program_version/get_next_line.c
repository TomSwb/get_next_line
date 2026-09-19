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
		char		*line;
		static char	*lftvr; 
		ssize_t		i;
		size_t j;
		ssize_t *reading;
	
		line = ft_extract_buffer(fd, &reading);
		if (line == NULL)
			return (NULL);
		i = 0;
		while (i < reading || line[i] != '\n')
			i++;
		j = 0;
		if (i != reading)
		{
			while (i < reading)
			{
				lftvr[j] = line[i];
				i++;
				j++;
			}
		}
		return (line);
}