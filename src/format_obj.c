/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 23:40:39 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 22:35:30 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	update_obj_matrix(t_obj *obj)
{
	obj->model_matrix = translation_matrix(identity_matrix(), obj->origin);
	obj->model_matrix = rotation_matrix(obj->model_matrix,
(obj->rotation.x * M_PI) / 180.0, (t_vec3f){1, 0, 0});
	obj->model_matrix = rotation_matrix(obj->model_matrix,
(obj->rotation.y * M_PI) / 180.0, (t_vec3f){0, 1, 0});
	obj->model_matrix = rotation_matrix(obj->model_matrix,
(obj->rotation.z * M_PI) / 180.0, (t_vec3f){0, 0, 1});
	obj->model_matrix = translation_matrix(obj->model_matrix,
sub_vec3f(obj->position, obj->origin));
	obj->model_matrix = scale_matrix(obj->model_matrix, obj->scale);
}

void	init_obj(t_obj *obj)
{
	obj->meshs = NULL;
	obj->nb_mesh = 0;
	obj->position = (t_vec3f){0, 0, 0};
	obj->origin = (t_vec3f){0, 0, 0};
	obj->rotation = (t_vec3f){0, 0, 0};
	obj->scale = (t_vec3f){1, 1, 1};
	obj->model_matrix = identity_matrix();
	obj->name[0] = '\0';
	obj->load = false;
}

int		format_obj(t_obj *obj, t_load_vertex *array)
{
	uint	i;

	i = 0;
	while (i < obj->nb_mesh)
	{
		if (!format_mesh(&obj->meshs[i], array))
			return (0);
		++i;
	}
	return (0);
}
