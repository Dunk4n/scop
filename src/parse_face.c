/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_face.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 15:37:30 by niduches          #+#    #+#             */
/*   Updated: 2020/06/11 20:23:11 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
**nb_vertex is temporarily capacity of index
*/
static int	put_triangle_in(t_vec3ui triangle[3],
t_load_vertex *array, t_mesh *mesh)
{
	uint	i;

	i = 0;
	while (i < 3)
	{
		if (triangle[i].x != (uint)-1 && triangle[i].x > array->nb_position)
			return (0);
		if (triangle[i].y != (uint)-1 && triangle[i].y > array->nb_texture)
			return (0);
		if (triangle[i].z != (uint)-1 && triangle[i].z > array->nb_normal)
			return (0);
		mesh->index[mesh->nb_index * 9 + 3 * i] = triangle[i].x;
		mesh->index[mesh->nb_index * 9 + 1 + 3 * i] = triangle[i].z;
		mesh->index[mesh->nb_index * 9 + 2 + 3 * i] = triangle[i].y;
		++i;
	}
	++mesh->nb_index;
	return (1);
}

static int	add_index_triangle(t_vec3ui triangle[3],
t_load_vertex *array, t_mesh *mesh)
{
	uint	*tmp;
	uint	i;

	if (mesh->nb_vertex > mesh->nb_index)
	{
		if (!put_triangle_in(triangle, array, mesh))
			return (0);
		return (1);
	}
	tmp = mesh->index;
	mesh->nb_vertex = (!mesh->nb_vertex) ? 1 : mesh->nb_vertex * 2;
	if (!(mesh->index = malloc(sizeof(uint) * mesh->nb_vertex * 9)))
		return (0);
	i = 0;
	while (i < mesh->nb_index * 9)
	{
		mesh->index[i] = tmp[i];
		++i;
	}
	free(tmp);
	if (!put_triangle_in(triangle, array, mesh))
		return (0);
	return (1);
}

static uint	get_arg_face(char *line, t_vec3ui *vec)
{
	uint	i;
	uint	tmp;

	*vec = (t_vec3ui){0, (uint)-1, (uint)-1};
	i = get_uint(line, &vec->x);
	if (*(line + i) != '/')
		return (i);
	++i;
	tmp = get_uint(line + i, &vec->y);
	if (!tmp || vec->y == 0)
		vec->y = (uint)-1;
	i += tmp;
	if (*(line + i) != '/')
		return (i);
	++i;
	tmp = get_uint(line + i, &vec->z);
	if (!tmp || vec->z == 0)
		vec->z = (uint)-1;
	i += tmp;
	return (i);
}

int		parse_face(char *line, t_load_vertex *array, t_mega_obj *mega)
{
	t_vec3ui		triangle[3];
	unsigned int	i;

	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	line += get_arg_face(line, triangle);
	line += pass_spaces(line);
	line += get_arg_face(line, triangle + 1);
	line += pass_spaces(line);
	if (!*line || triangle[0].x == 0 || triangle[0].y == 0 || triangle[0].z == 0
	|| triangle[1].x == 0 || triangle[1].y == 0 || triangle[1].z == 0)
		return (0);
	while (*line)
	{
		i = get_arg_face(line, triangle + 2);
		if (!i ||
		triangle[2].x == 0 || triangle[2].y == 0 || triangle[2].z == 0)
			return (0);
		line += pass_spaces(line + i) + i;
		if (!add_index_triangle(triangle, array, get_actual_mesh(mega)))
			return (0);
		triangle[1] = triangle[2];
	}
	return (1);
}
