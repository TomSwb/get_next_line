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

        if (data != NULL && (ft_strchr(data, '\n') != 0 
            || ft_strlen(data) < BUFFER_SIZE))
        {
            if (!ft_extract_line(&line, &data));
                return (NULL);
            return (line);
        }
        while (ft_strchr(data, '\n') != 0 
                || ft_strlen(data) < BUFFER_SIZE)
            ft_extract_buffer(fd, &data);
        if (!(ft_extract_line(&line, &data));
            return (NULL);
		return (line);
}
