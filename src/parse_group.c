/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_group.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 18:57:34 by niduches          #+#    #+#             */
/*   Updated: 2020/06/20 19:06:14 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int	add_new_mesh(t_obj *obj)
{
	t_mesh			*tmp;
	unsigned int	i;

	tmp = obj->meshs;
	if (!(obj->meshs = malloc(sizeof(t_mesh) * (obj->nb_mesh + 1))))
		return (0);
	i = 0;
	while (i < obj->nb_mesh)
	{
		obj->meshs[i] = tmp[i];
		++i;
	}
	obj->meshs[obj->nb_mesh].material = tmp[obj->nb_mesh - 1].material;
	++obj->nb_mesh;
	free(tmp);
	return (1);
}

int			parse_group(char *line, t_load_vertex *array, t_mega_obj *mega)
{
	uint	material;
	char	name[64];
	int		j;

	(void)array;
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	j = pass_word(line);
	ft_strncpy(name, line, (j > 63) ? 63 : j);
	line += pass_spaces(line + j) + j;
	if (*line)
		return (0);
	material = get_actual_mesh(mega)->material;
	if (get_actual_mesh(mega)->nb_index > 0 &&
!add_new_mesh(get_actual_obj(mega)))
		return (0);
	init_mesh(get_actual_mesh(mega));
	ft_strcpy(get_actual_mesh(mega)->name, name);
	get_actual_mesh(mega)->material = material;
	return (1);
}
