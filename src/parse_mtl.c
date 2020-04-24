/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mtl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 01:09:50 by niduches          #+#    #+#             */
/*   Updated: 2020/04/25 01:13:54 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		parse_mtllib(char *line, t_load_vertex *array, t_mega_obj *mega)
{
	(void)array;
	(void)mega;
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	if (*line)
		return (0);
	return (1);
}

int		parse_usemtl(char *line, t_load_vertex *array, t_mega_obj *mega)
{
	(void)array;
	(void)mega;
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	if (*line)
		return (0);
	return (1);
}
