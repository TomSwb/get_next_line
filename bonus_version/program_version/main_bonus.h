/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomswb <tomswb@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:53:07 by tomswb            #+#    #+#             */
/*   Updated: 2026/09/24 18:53:11 by tomswb           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_BONUS_H
# define MAIN_BONUS_H

// ** Library ** //

# include "get_next_line_bonus.h"

// ** Functions ** //

// main_bonus_utils.c
void	stdin_gnl(void);
void	files_gnl(char **av);
int		*allocate_fds(char **av, size_t *i);
int		check_fds(int *fds, size_t len);
void	process_fd_line(int *fds, size_t i);

#endif