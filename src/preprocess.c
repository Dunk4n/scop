/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preporcess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 22:50:19 by niduches          #+#    #+#             */
/*   Updated: 2020/06/09 00:21:44 by niduches         ###   ########.fr       */
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
	while (i < mesh->nb_vertex && (!*tex || !*norm))
	{
		if (mesh->vertex[i].normal.x || mesh->vertex[i].normal.y ||
mesh->vertex[i].normal.z)
			*norm = true;
		if (mesh->vertex[i].texcoord.x || mesh->vertex[i].texcoord.y)
			*tex = true;
		++i;
	}
}

static void	preprocess_mesh_rand(t_mesh *mesh)
{
	uint	i;
	bool	tex;
	bool	norm;

	if (!mesh)
		return ;
	is_empty_norm_tex(&norm, &tex, mesh);
	if (norm && tex)
		return ;
	i = 0;
	while (i < mesh->nb_vertex)
	{
		if (!norm)
		{
			mesh->vertex[i].normal = (t_vec3f){(float)(rand() % 100) / 100.0,
(float)(rand() % 100) / 100.0, (float)(rand() % 100) / 100.0};
		}
		if (!tex)
			mesh->vertex[i].texcoord =
(t_vec2f){(float)(rand() % 100) / 100.0, (float)(rand() % 100) / 100.0};
		++i;
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
