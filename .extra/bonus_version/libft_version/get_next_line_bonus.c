/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomswb <tomswb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:56:37 by tomswb            #+#    #+#             */
/*   Updated: 2026/09/24 19:23:45 by tomswb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
* @brief
Returns a pointer to the next available line from the file pointed out by 'fd'.

Depends on:
	find_node();
		create_node();
			malloc();

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

	free_what_node();
		free_node();
			free();

* @param int fd 
* @return char* 
*/
char	*get_next_line(int fd)
{
	static t_node	*list;
	t_node			*file;
	char			*line;
	ssize_t			reading;

	file = find_node(fd, &list);
	if (!file)
		return (free_what_node(fd, &list));
	while (file->data == NULL || find_c_index(file->data, '\n') < 0)
	{
		reading = extract_buffer(fd, &file->data);
		if (reading < 0)
			return (free_what_node(fd, &list));
		if (reading == 0)
			break ;
	}
	if (file->data == NULL)
		return (free_what_node(fd, &list));
	if (extract_line(&line, &file->data))
		return (free_what_node(fd, &list));
	return (line);
}

/**
* @brief 
Returns a pointer to the node corresponding to the given 'fd' and containing the 
related data.

Depends on:
	create_node();
		malloc();

* @param int fd 
* @param t_node **list 
* @return t_node* 
*/
t_node	*find_node(int fd, t_node **list)
{
	t_node	*node;
	t_node	*temp;

	if (*list == NULL)
	{
		*list = create_node(fd);
		return (*list);
	}
	temp = *list;
	while (temp->next != NULL)
	{
		if (temp->fd == fd)
			return (temp);
		temp = temp->next;
	}
	if (temp->fd == fd)
		return (temp);
	node = create_node(fd);
	temp->next = node;
	return (node);
}

/**
* @brief 
Returns a pointer to a new node for the related 'fd'.

External:
	malloc();

* @param int fd 
* @return t_node* 
*/
t_node	*create_node(int fd)
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

/**
* @brief 
Finds the node related to the given 'fd', returning the result of 
freeing said node

Depends on:
	free_node();
		free();

* @param int fd 
* @param t_node **list 
* @return void* 
*/
void	*free_what_node(int fd, t_node **list)
{
	t_node	*target;

	if (!list || *list == NULL)
		return (NULL);
	target = *list;
	if (target->fd != fd)
	{
		while (target->next != NULL && target->next->next != NULL)
		{
			if (target->next->fd != fd)
				target = target->next;
			else if (target->next->fd == fd)
				return (free_node(target, list, 0));
		}
		if (target->next == NULL)
			return (NULL);
		else if (target->next->fd != fd)
			return (NULL);
		else
			return (free_node(target, list, 0));
	}
	else
		return (free_node(target, list, 1));
}

/**
* @brief 
Frees the 'target' node, ensuring the head is still connected to the list
depending if 'is_head' or not. If not head, ensure previous node is still
connected.

External:
	free();

* @param t_node *target 
* @param t_node **list 
* @param int is_head 
* @return void* 
*/
void	*free_node(t_node *target, t_node **list, int is_head)
{
	t_node	*link;

	if (!is_head)
	{
		link = target;
		target = target->next;
		link->next = target->next;
		free(target->data);
		free(target);
	}
	else
	{
		link = target->next;
		free(target->data);
		free(target);
		*list = link;
	}
	return (NULL);
}
