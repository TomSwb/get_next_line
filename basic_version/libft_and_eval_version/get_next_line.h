/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomswb <tomswb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:53:07 by tomswb            #+#    #+#             */
/*   Updated: 2026/09/23 16:39:19 by tomswb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// ** Libraries ** //

# include <unistd.h>
// read();

# include <stdlib.h>
// malloc();
// free();

# include <stddef.h>
// size_t

// ** BUFFER_SIZE handling ** //

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

// ** Functions ** //

// get_next_line.c
char	*get_next_line(int fd);

// get-next_line_utils.c
ssize_t	find_c_index(char *s, int c);
ssize_t	extract_buffer(int fd, char **data);
char	*cat_buffer_data(char *buffer, char **data);
int		extract_line(char **line, char **data);
void	clean_data(char **data, ssize_t len);

#endif