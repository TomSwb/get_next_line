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

int	ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if ((uncigned char)s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t ft_strlen(char *s)
{
    size_t len;
    
    while (s[len])
        len++;
    return (len);
}

int	ft_extract_line(char *line, char *data)
{
	size_t len;
	size_t	i;

	len = ft_strchr(data, '\n');
	line = malloc(len + 1);
	if (!line)
		return (1);
	i = 0;
	while (i < len)
	{
		line[i] = data[i];
		i++;
	}
	line[len + 1] = '\0';
	return (0);
}

ssize_t ft_extract_buffer(int fd, char *data)
{
	char		*buffer;
    ssize_t reading;
    size_t i;
    size_t j;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (1);
	reading = read(fd, buffer, BUFFER_SIZE);
	if (reading == -1)
	{
		free(buffer);
		return (reading);
	}
	buffer[reading] = '\0';
    i = ft_strlen(data);
    j = 0;
    while (buffer[j])
    {
        data[i + j] = buffer[j];
        j++;
    }
	return (reading);
}

char *ft_freedata(char **data)
{
	free(*data);
	*data = NULL;
	return (NULL);
}
