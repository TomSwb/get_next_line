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
	char		*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	*reading = read(fd, buffer, BUFFER_SIZE);
	if (*reading == -1)
	{
		free(buffer);
		return (NULL);
	}
	buffer[*reading] = '\0';
	return (buffer);
}

size_t ft_setlen(char *lftvr, size_t *reading, char *buffer)
{
	size_t len;
	size_t i;
	
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
		return (len);
}
