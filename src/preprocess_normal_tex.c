/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_normal_tex.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:08:55 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 17:51:16 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static t_vec3f	get_normal(t_vec3f a, t_vec3f b, t_vec3f c)
{
	t_vec3f	normal;

	b = sub_vector(b, a);
	c = sub_vector(c, a);
	normal = cross_vector(b, c);
	return (normalize_vector(normal));
}

static void		preprocess_set_normal(t_mesh *mesh, uint i)
{
	t_vec3f	normal;

	normal = get_normal(mesh->vertex[mesh->index[i]].position, mesh->
vertex[mesh->index[i + 1]].position, mesh->vertex[mesh->index[i + 2]].position);
	mesh->vertex[mesh->index[i]].normal = normal;
	mesh->vertex[mesh->index[i + 1]].normal = normal;
	mesh->vertex[mesh->index[i + 2]].normal = normal;
}

static void		is_empty_norm_tex(bool *norm, bool *tex, t_mesh *mesh)
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

static void		preprocess_set_tex(t_mesh *mesh, uint i, bool *square,
bool color)
{
	mesh->vertex[mesh->index[i]].texcoord = *square ?
	(t_vec2f){1.0, 1.0} : (t_vec2f){0.0, 0.0};
	mesh->vertex[mesh->index[i + (*square ? 2 : 1)]].texcoord =
	(t_vec2f){1.0, 0.0};
	mesh->vertex[mesh->index[i + (*square ? 1 : 2)]].texcoord =
	(t_vec2f){0.0, 1.0};
	*square = !*square;
	if (color)
	{
		mesh->vertex[mesh->index[i + 1]].color =
		mesh->vertex[mesh->index[i]].color;
		mesh->vertex[mesh->index[i + 2]].color =
		mesh->vertex[mesh->index[i]].color;
	}
}

void			preprocess_mesh_rand(t_mesh *mesh)
{
	uint	i;
	bool	tex;
	bool	norm;
	bool	square;

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
			preprocess_set_normal(mesh, i);
		if (!tex)
			preprocess_set_tex(mesh, i, &square, !tex && !norm);
		i += 3;
	}
}
