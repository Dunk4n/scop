/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preporcess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 22:50:19 by niduches          #+#    #+#             */
/*   Updated: 2020/06/12 04:01:43 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	get_all_value(double *x, double *y, double *z, t_mesh *mesh)
{
	uint	i;

	i = 0;
	while (i < mesh->nb_vertex)
	{
		*x += mesh->vertex[i].position.x;
		*y += mesh->vertex[i].position.y;
		*z += mesh->vertex[i++].position.z;
	}
}

static void	preprocess_mesh_pos(t_mesh *mesh)
{
	uint	i;
	double	x;
	double	y;
	double	z;

	if (!mesh || !mesh->nb_vertex)
		return ;
	i = 0;
	x = 0;
	y = 0;
	z = 0;
	get_all_value(&x, &y, &z, mesh);
	x /= mesh->nb_vertex;
	y /= mesh->nb_vertex;
	z /= mesh->nb_vertex;
	i = 0;
	while (i < mesh->nb_vertex)
	{
		mesh->vertex[i].color = (t_vec3f){(float)(rand() % 100) / 100.0,
(float)(rand() % 100) / 100.0, (float)(rand() % 100) / 100.0};
		mesh->vertex[i].position.x -= x;
		mesh->vertex[i].position.y -= y;
		mesh->vertex[i++].position.z -= z;
	}
}

static void	is_empty_norm_tex(bool *norm, bool *tex, t_mesh *mesh)
{
	uint	i;

	*tex = false;
	*norm = false;
	i = 0;
	while (i < mesh->nb_vertex && !*tex && !*norm)
	{
		if (mesh->vertex[i].normal.x || mesh->vertex[i].normal.y ||
mesh->vertex[i].normal.z)
			*norm = true;
		if (mesh->vertex[i].texcoord.x || mesh->vertex[i].texcoord.y)
			*tex = true;
		++i;
	}
}

static t_vec3f	get_normal(t_vec3f a, t_vec3f b, t_vec3f c)
{
	t_vec3f	normal;

	b = sub_vector(b, a);
	c = sub_vector(c, a);
	normal = cross_vector(b, c);
	return (normalize_vector(normal));
}

static void	preprocess_mesh_rand(t_mesh *mesh)
{
	uint	i;
	bool	tex;
	bool	norm;
	bool	square;
	t_vec3f	normal;

	if (!mesh)
		return ;
	is_empty_norm_tex(&norm, &tex, mesh);
	if (norm && tex)
		return ;
	square = false;
	i = 0;
	while (i < mesh->nb_index)
	{
		if (!norm)
		{
			normal = get_normal(mesh->vertex[mesh->index[i]].position,
mesh->vertex[mesh->index[i + 1]].position, mesh->vertex[mesh->index[i + 2]].position);
			mesh->vertex[mesh->index[i]].normal = normal;
			mesh->vertex[mesh->index[i + 1]].normal = normal;
			mesh->vertex[mesh->index[i + 2]].normal = normal;
		}
		if (!tex)
		{
			if (square)
				mesh->vertex[mesh->index[i]].texcoord = (t_vec2f){1.0, 1.0};
			else
				mesh->vertex[mesh->index[i]].texcoord = (t_vec2f){0.0, 0.0};
			mesh->vertex[mesh->index[i + (square ? 2 : 1)]].texcoord = (t_vec2f){1.0, 0.0};
			mesh->vertex[mesh->index[i + (square ? 1 : 2)]].texcoord = (t_vec2f){0.0, 1.0};
			square = !square;
		}
		if (!tex && !norm)
		{
			mesh->vertex[mesh->index[i + 1]].color = mesh->vertex[mesh->index[i]].color;
			mesh->vertex[mesh->index[i + 2]].color = mesh->vertex[mesh->index[i]].color;
		}
		i += 3;
	}
}

void		preprocess_mega(t_mega_obj *mega)
{
	uint	i;
	uint	j;

	if (!mega)
		return ;
	i = 0;
	while (i < mega->nb_obj)
	{
		j = 0;
		while (j < mega->objs[i].nb_mesh)
		{
			preprocess_mesh_pos(mega->objs[i].meshs + j);
			preprocess_mesh_rand(mega->objs[i].meshs + j);
			++j;
		}
		++i;
	}
}
