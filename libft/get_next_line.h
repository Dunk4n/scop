/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:17:40 by niduches          #+#    #+#             */
/*   Updated: 2020/06/10 22:03:39 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# define NB_FD 5

# include "libft.h"

typedef struct	s_nl
{
	short	fd;
	char	buff[BUFFER_SIZE];
}				t_nl;

int				get_next_line(int fd, char **line);

#endif
