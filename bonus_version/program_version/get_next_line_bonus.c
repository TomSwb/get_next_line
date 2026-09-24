/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomswb <tomswb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:56:37 by tomswb            #+#    #+#             */
/*   Updated: 2026/09/23 17:38:44 by tomswb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_node	*list;
	t_node			*file;
	char			*line;
	ssize_t			reading;

	file = find_node(fd, &list);
	if (!file)
		return (free_node(fd, &list));
	while (file->data == NULL || find_c_index(file->data, '\n') < 0)
	{
		reading = extract_buffer(fd, &file->data);
		if (reading < 0)
			return (free_node(fd, &list));
		if (reading == 0)
			break;
	}
	if (file->data == NULL)
		return (NULL);
	if (extract_line(&line, &file->data))
		return (free_node(fd, &list));
	return (line);
}

t_node	*find_node(int fd, t_node **list)
{
	t_node	*node;
	t_node *temp;
	
	if (*list == NULL)
	{
		*list = create_node(fd);
		return (*list);
	}
	temp = *list;
	while (temp->next != NULL)
	{
		if (temp->fd == fd)
		{
			node = temp;
			return (node);
		}
		temp = temp->next;
	}
	if (temp->fd == fd)
	{
			node = temp;
			return (node);
	}
	node = create_node(fd);
	temp->next = node;
	return (node);
}

t_node *create_node(int fd)
{
	t_node	*node;
	
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->data = NULL;
	node->next = NULL;
	return (node);
}

void *free_node(int fd, t_node **list)
{
	t_node *target;
	t_node *previous;
	
	target = *list;
	while (target->next->fd != fd)
		target = target->next;
	previous = target;
	target = target->next;
	previous->next = target->next;
	free(target->data);
	free(target);
	return (NULL);
}

char	*free_data(char *data)
{
	free(data);
	data = NULL;
	return (NULL);
}
