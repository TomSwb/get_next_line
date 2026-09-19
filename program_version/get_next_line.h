/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomswb <tomswb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:53:07 by tomswb            #+#    #+#             */
/*   Updated: 2026/09/19 17:40:40 by tomswb           ###   ########.fr       */
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
char	*ft_extract_buffer(int fd, ssize_t *reading);

#endif