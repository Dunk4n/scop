/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 22:00:32 by niduches          #+#    #+#             */
/*   Updated: 2020/06/19 19:11:01 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

uint	pass_nb(char *line)
{
	uint	i;

	i = 0;
	if (*line == '-')
		++i;
	while (line[i] >= '0' && line[i] <= '9')
		++i;
	return (i);
}

int		parse_s(char *line, t_load_vertex *array, t_mega_obj *mega)
{
	(void)array;
	(void)mega;
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	if (!*line)
		return (0);
	if (!ft_strcmp(line, "off"))
		line += 3;
	else if (*line == '-' || (*line >= '0' && *line <= '9'))
		line += pass_nb(line);
	else
		return (0);
	line += pass_spaces(line);
	if (*line)
		return (0);
	return (1);
}
