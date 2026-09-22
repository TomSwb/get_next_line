/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomswb <tomswb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:56:40 by tomswb            #+#    #+#             */
/*   Updated: 2026/09/22 17:40:02 by tomswb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

ssize_t	find_c_index(char *s, int c)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if ((unsigned char)s[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

ssize_t extract_buffer(int fd, char **data)
{
	char	*buffer;
	ssize_t	reading;
	char	*temp;

	if (BUFFER_SIZE <= 0)
		return (-1);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	reading = read(fd, buffer, BUFFER_SIZE);
	if (reading <= 0)
	{
		free(buffer);
		return (reading);
	}
	buffer[reading] = '\0';
	temp = cat_buffer_data(buffer, data);
	free(buffer);
	if (temp == NULL)
		return (-1);
	*data = temp;
	return (reading);
}

char	*cat_buffer_data(char *buffer, char **data)
{
	char	*temp;
    size_t i;
    size_t j;

	temp = malloc(find_c_index(buffer, '\0') + find_c_index(*data, '\0') + 1);
	if (!temp)
		return (NULL);
	i = 0;
	if (*data != NULL)
	{
		while ((*data)[i])
		{
			temp[i] = (*data)[i];
			i++;
		}
	}
	j = 0;
	while (buffer[j])
	{
		temp[i + j] = buffer[j];
		j++;
	}
	temp[i + j] = '\0';
	free(*data);
	return (temp);
}

int	extract_line(char **line, char **data)
{
	ssize_t len;
	ssize_t	i;

	len = find_c_index(*data, '\n');
	if (len == -1)
		len = find_c_index(*data, '\0');
	else
	 	len += 1;
	(*line) = malloc(len + 1);
	if (!(*line))
		return (1);
	i = 0;
	while (i < len)
	{
		(*line)[i] = (*data)[i];
		i++;
	}
	(*line)[i] = '\0';
	clean_data(data, len);
	return (0);
}

void	clean_data(char **data, ssize_t len)
{
	ssize_t	i;
	ssize_t	n;

	i = 0;
	n = find_c_index((*data) + len, '\0') + 1;
	while (i < n)
	{
		(*data)[i] = (*data)[len + i];
		i++;
	}
	if ((*data)[0] == '\0')
	{
		free(*data);
		*data = NULL;
	}
}
