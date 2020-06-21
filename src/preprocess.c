/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preporcess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 22:50:19 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 17:53:21 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	get_all_value(double *x, double *y, double *z, t_mesh *mesh)
{
	uint	i;

	*x = 0;
	*y = 0;
	*z = 0;
	i = 0;
	while (i < mesh->nb_vertex)
	{
		*x += mesh->vertex[i].position.x;
		*y += mesh->vertex[i].position.y;
		*z += mesh->vertex[i++].position.z;
	}
	*x /= mesh->nb_vertex;
	*y /= mesh->nb_vertex;
	*z /= mesh->nb_vertex;
}

static void	preprocess_mesh_pos(t_mesh *mesh, bool color, bool pos)
{
	uint	i;
	double	x;
	double	y;
	double	z;
	float	tmp;

	if (!mesh || !mesh->nb_vertex)
		return ;
	get_all_value(&x, &y, &z, mesh);
	i = 0;
	while (i < mesh->nb_vertex)
	{
		tmp = (float)(rand() % 1000) / 1000.0;
		mesh->vertex[i].color = color ? (t_vec3f){tmp, (float)(rand() % 1000) /
1000.0, (float)(rand() % 1000) / 1000.0} : (t_vec3f){tmp, tmp, tmp};
		if (!pos)
		{
			mesh->vertex[i].position.x -= x;
			mesh->vertex[i].position.y -= y;
			mesh->vertex[i].position.z -= z;
		}
		++i;
	}
}

void		preprocess_mega(t_mega_obj *mega, bool color, bool pos)
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
			preprocess_mesh_pos(mega->objs[i].meshs + j, color, pos);
			preprocess_mesh_rand(mega->objs[i].meshs + j);
			if (!pos)
				mega->objs[i].meshs[j].position.y =
				(j - (mega->objs[i].nb_mesh - 1) / 2.0) * 8;
			mega->objs[i].meshs[j].origin.y = mega->objs[i].position.x;
			++j;
		}
		if (!pos)
			mega->objs[i].position.x = (i - (mega->nb_obj - 1) / 2.0) * 8;
		mega->objs[i].origin.x = mega->objs[i].position.x;
		++i;
	}
}
