/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomswb <tomswb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:56:40 by tomswb            #+#    #+#             */
/*   Updated: 2026/09/24 19:22:23 by tomswb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
* @brief 
Returns a ssize_t representing the index of 'c' in 's'.
The return value is equal to len of 's' up to 'c'.

* @param char *s 
* @param int c 
* @return ssize_t 
*/
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

/**
* @brief 
Returns ssize_t 'reading' indicating eof or not.
Extract the 'buffer' into 'data', ensuring allocation and calling
concatenation function if 'data' isn't empty. 

Depends on:
	cat_buffer_data();
		find_c_index();
		malloc();
		free();

External:
	malloc();
	free();

* @param int fd 
* @param char **data 
* @return ssize_t 
*/
ssize_t	extract_buffer(int fd, char **data)
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

/**
* @brief 
Returns a concatenation of 'buffer' into 'data' if data is not empty
or simply it's copy if 'data' is empty.

Depends on:
	find_c_index();

External:
	malloc();
	free();

* @param char *buffer 
* @param char **data 
* @return char* 
*/
char	*cat_buffer_data(char *buffer, char **data)
{
	char	*temp;
	size_t	i;
	size_t	j;

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

/**
* @brief 
Returns a success boolean.
Extract the present line in 'data' intp the pointed 'line' 
for printing in GNL.

Depends on:
	find_c_index();
	clean_data();
		find_c_index();
		free();

External:
	malloc();

* @param char **line 
* @param char **data 
* @return int 
*/
int	extract_line(char **line, char **data)
{
	ssize_t	len;
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
