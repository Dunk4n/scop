/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 23:40:39 by niduches          #+#    #+#             */
/*   Updated: 2020/06/11 19:49:21 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static t_vertex	generate_vertex(uint idx, uint *old_idx, t_load_vertex *array)
{
	t_vertex	new;

	if (old_idx[idx * 3] == (uint)-1 || old_idx[idx * 3] > array->nb_position ||
old_idx[idx * 3] == 0)
		new.position = (t_vec3f){0, 0, 0};
	else
		new.position = array->position[old_idx[idx * 3] - 1];
	if (old_idx[idx * 3 + 1] == (uint)-1 || old_idx[idx * 3 + 1] >
array->nb_normal || old_idx[idx * 3 + 1] == 0)
		new.normal = (t_vec3f){0, 0, 0};
	else
		new.normal = array->normal[old_idx[idx * 3 + 1] - 1];
	if (old_idx[idx * 3 + 2] == (uint)-1 || old_idx[idx * 3 + 2] >
array->nb_texture || old_idx[idx * 3 + 2] == 0)
		new.texcoord = (t_vec2f){0, 0};
	else
		new.texcoord = array->texture[old_idx[idx * 3 + 2] - 1];
	new.color = (t_vec3f){0, 0, 0};
	return (new);
}

static uint		put_vertex_in_array(t_vertex new, t_vertex *vertex,
uint *nb_vertex, bool opti)
{
	uint	i;
	t_vertex *tmp = vertex;

	if (opti)
	{
		i = 0;
		while (i < *nb_vertex)
		{
			if (!ft_memcmp((void*)vertex, (void*)(&new), sizeof(t_vertex)))
				return (i);
			++vertex;
			++i;
		}
		*vertex = new;
		++(*nb_vertex);
		return (i);
	}
	tmp[*nb_vertex] = new;
	++(*nb_vertex);
	return (*nb_vertex - 1);
}

static int		reduce_vertex(t_vertex **vertex, uint nb_vertex)
{
	t_vertex	*tmp;
	uint		i;

	tmp = *vertex;
	if (!(*vertex = malloc(sizeof(t_vertex) * nb_vertex)))
	{
		free(tmp);
		return (0);
	}
	i = 0;
	while (i < nb_vertex)
	{
		(*vertex)[i] = tmp[i];
		++i;
	}
	free(tmp);
	return (1);
}

static bool	is_optimisable(t_mesh *mesh, t_load_vertex *array)
{
	uint	i;
	bool	opti;

	i = 0;
	opti = false;
	while (i < mesh->nb_index && !opti)
	{
		if (mesh->index[i * 3 + 1] != (uint)-1 && ft_memcmp(&array->normal[
mesh->index[i * 3 + 1] - 1], &(t_vec3f){0, 0, 0}, sizeof(t_vec3f)))
			opti = true;
		if (mesh->index[i * 3 + 2] != (uint)-1 && ft_memcmp(&array->texture[
mesh->index[i * 3 + 2] - 1], &(t_vec2f){0, 0}, sizeof(t_vec2f)))
			opti = true;
		++i;
	}
	return (opti);
}

static int		format_mesh(t_mesh *mesh, t_load_vertex *array)
{
	uint	*old_idx;
	uint	i;
	bool	opti;

	old_idx = mesh->index;
	mesh->nb_index *= 3;
	opti = is_optimisable(mesh, array);
	if (!(mesh->vertex = malloc(sizeof(t_vertex) * mesh->nb_index)))
		return (0);
	if (!(mesh->index = malloc(sizeof(uint) * mesh->nb_index)))
		return (0);
	mesh->nb_vertex = 0;
	i = 0;
	while (i < mesh->nb_index)
	{
		mesh->index[i] = put_vertex_in_array(generate_vertex(i, old_idx, array),
mesh->vertex, &mesh->nb_vertex, opti);
		++i;
	}
	free(old_idx);
	if (mesh->nb_vertex != mesh->nb_index &&
	!(reduce_vertex(&mesh->vertex, mesh->nb_vertex)))
		return (0);
	return (1);
}

int				format_obj(t_obj *obj, t_load_vertex *array)
{
	uint	i;

	i = 0;
	while (i < obj->nb_mesh)
	{
		if (!format_mesh(&obj->meshs[i], array))
		{
			free(array->position);
			array->position = NULL;
			free(array->normal);
			array->normal = NULL;
			free(array->texture);
			array->texture = NULL;
			return (0);
		}
		++i;
	}
	free(array->position);
	free(array->normal);
	free(array->texture);
	ft_bzero((void*)(array), sizeof(t_load_vertex));
	return (0);
}
