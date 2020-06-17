/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mtl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 01:09:50 by niduches          #+#    #+#             */
/*   Updated: 2020/06/17 11:57:01 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int			parse_mtllib(char *line, t_load_vertex *array, t_mega_obj *mega)
{
	uint	size;
	char	*pos;

	(void)array;
	(void)mega;
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	pos = line;
	size = pass_word(line);
	if (!size)
		return (0);
	line += pass_word(line);
	line += pass_spaces(line);
	if (*line)
		return (0);
	*(pos + size) = '\0';
	if (!get_material(pos, mega))
		return (0);
	return (1);
}

static unsigned int	get_index_material(char *name, t_mega_obj *mega)
{
	uint	i;

	i = 0;
	while (i < mega->nb_material)
	{
		if (!ft_strcmp(name, mega->materials[i++].name))
			return (i);
	}
	return (0);
}

int			parse_usemtl(char *line, t_load_vertex *array, t_mega_obj *mega)
{
	char	name[64];
	uint	i;
	uint	size;

	(void)array;
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	i = 0;
	size = pass_word(line);
	if (!size || size > 63)
		return (0);
	while (i < size)
	{
		name[i] = *line;
		++i;
		++line;
	}
	name[i] = '\0';
	get_actual_mesh(mega)->material = get_index_material(name, mega);
	line += pass_spaces(line);
	if (*line)
		return (0);
	return (1);
}
