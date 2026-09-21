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

int ft_extract_buffer(int fd, char *data)
{
	char		*buffer;
    size_t reading;
    size_t i;
    size_t j;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	reading = read(fd, buffer, BUFFER_SIZE);
	if (reading == -1)
	{
		free(buffer);
		return (0);
	}
	buffer[reading] = '\0';
    i = ft_strlen(data);
    j = 0;
    while (buffer[j])
    {
        data[i + j] = buffer[j];
        j++;
    }
	return (1);
}

size_t ft_strlen(char *s)
{
    size_t len;
    
    while (s[len])
        len++;
    return (len);
}
