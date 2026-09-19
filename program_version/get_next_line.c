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
		char		*buffer;
		char  *line;
		static char	*lftvr = NULL; 
		ssize_t *reading;
        size_t len;
        size_t i;
	
		buffer = ft_extract_buffer(fd, &reading);
		if (buffer == NULL)
			return (NULL);
        if (lftvr != NULL)
            len = ft_strlen(lftvr);
		if (reading != BUFFER_SIZE)
            len += reading;
        else
        {
            if (ft_strchr(buffer, '\n');
            {
                i = 0;
                while (buffer[i] != '\n')
                {
                    len++;
                    i++;
                }
            }
            else
                len += reading;
        }
        return (line);
}
