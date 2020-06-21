/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 01:01:06 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 01:46:43 by niduches         ###   ########.fr       */
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

void	move_mega(t_mega_obj *mega, t_vec3f move)
{
	uint	i;

	i = 0;
	while (i < mega->nb_obj)
	{
		mega->objs[i].position.x += move.x;
		mega->objs[i].position.y += move.y;
		mega->objs[i].position.z += move.z;
		++i;
	}
}

void	move_origine_mega(t_mega_obj *mega, t_vec3f move)
{
	uint	i;

	i = 0;
	while (i < mega->nb_obj)
	{
		mega->objs[i].origin.x += move.x;
		mega->objs[i].origin.y += move.y;
		mega->objs[i].origin.z += move.z;
		++i;
	}
}

void	move_and_origine_mega(t_mega_obj *mega, t_vec3f move)
{
	uint	i;

	i = 0;
	while (i < mega->nb_obj)
	{
		mega->objs[i].position.x += move.x;
		mega->objs[i].position.y += move.y;
		mega->objs[i].position.z += move.z;
		mega->objs[i].origin.x += move.x;
		mega->objs[i].origin.y += move.y;
		mega->objs[i].origin.z += move.z;
		++i;
	}
}

void	rotate_mega(t_mega_obj *mega, t_vec3f rotate)
{
	uint	i;

	i = 0;
	while (i < mega->nb_obj)
	{
		mega->objs[i].rotation.x += rotate.x;
		while (mega->objs[i].rotation.x > 360)
			mega->objs[i].rotation.x -= 360;
		while (mega->objs[i].rotation.x < -360)
			mega->objs[i].rotation.x += 360;
		mega->objs[i].rotation.y += rotate.y;
		while (mega->objs[i].rotation.y > 360)
			mega->objs[i].rotation.y -= 360;
		while (mega->objs[i].rotation.y < -360)
			mega->objs[i].rotation.y += 360;
		mega->objs[i].rotation.z += rotate.z;
		while (mega->objs[i].rotation.z > 360)
			mega->objs[i].rotation.z -= 360;
		while (mega->objs[i].rotation.z < -360)
			mega->objs[i].rotation.z += 360;
		++i;
	}
}

void	scale_mega(t_mega_obj *mega, t_vec3f scale)
{
	uint	i;

	i = 0;
	while (i < mega->nb_obj)
	{
		mega->objs[i].scale.x = (mega->objs[i].scale.x + scale.x < 0) ?
		0 : (scale.x + mega->objs[i].scale.x);
		mega->objs[i].scale.y = (mega->objs[i].scale.y + scale.y < 0) ?
		0 : (scale.y + mega->objs[i].scale.y);
		mega->objs[i].scale.z = (mega->objs[i].scale.z + scale.z < 0) ?
		0 : (scale.z + mega->objs[i].scale.z);
		++i;
	}
}
