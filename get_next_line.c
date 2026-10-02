/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomswb <tomswb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:56:37 by tomswb            #+#    #+#             */
/*   Updated: 2026/09/24 19:24:36 by tomswb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
* @brief
Returns a pointer to the next available line from the file pointed out by 'fd'.

Depends on:
	find_c_index();
	
	extract_buffer();
		cat_buffer_data();
			find_c_index();
			malloc();
			free();
		malloc();
		free();
		
	extract_line();
		find_c_index();
		clean_data();
			find_c_index();
			free();
		malloc();

External:
	free();

* @param int fd 
* @return char* 
*/
char	*get_next_line(int fd)
{
	static char	*data;
	char		*line;
	ssize_t		reading;

	while (data == NULL || find_c_index(data, '\n') < 0)
	{
		reading = extract_buffer(fd, &data);
		if (reading < 0)
		{
			free(data);
			data = NULL;
			return (NULL);
		}
		if (reading == 0)
			break ;
	}
	if (data == NULL)
		return (NULL);
	if (extract_line(&line, &data))
	{
		free(data);
		data = NULL;
		return (NULL);
	}
	return (line);
}
