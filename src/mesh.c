/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 23:00:37 by niduches          #+#    #+#             */
/*   Updated: 2020/06/12 17:37:06 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	update_mesh_matrix(t_mesh *mesh, t_mat4 obj_model)
{
	mesh->model_matrix = translation_matrix(obj_model, mesh->origin);
	mesh->model_matrix =
rotation_matrix(mesh->model_matrix, (mesh->rotation.x * M_PI) / 180.0, (t_vec3f){1, 0, 0});
	mesh->model_matrix =
rotation_matrix(mesh->model_matrix, (mesh->rotation.y * M_PI) / 180.0, (t_vec3f){0, 1, 0});
	mesh->model_matrix =
rotation_matrix(mesh->model_matrix, (mesh->rotation.z * M_PI) / 180.0, (t_vec3f){0, 0, 1});
	mesh->model_matrix = translation_matrix(mesh->model_matrix, sub_vec3f(mesh->position, mesh->origin));
	mesh->model_matrix = scale_matrix(mesh->model_matrix, mesh->scale);
}

void	init_mesh(t_mesh *mesh)
{
	if (!mesh)
		return ;
	mesh->position = (t_vec3f){0, 0, 0};
	mesh->origin = (t_vec3f){0, 0, 0};
	mesh->rotation = (t_vec3f){0, 0, 0};
	mesh->scale = (t_vec3f){1, 1, 1};
	mesh->model_matrix = identity_matrix();
	mesh->array_obj = 0;
	mesh->array_buffer = 0;
	mesh->array_buffer_index = 0;
	mesh->vertex = NULL;
	mesh->index = NULL;
	mesh->nb_vertex = 0;
	mesh->nb_index = 0;
	mesh->material = 0;
	mesh->name[0] = '\0';
	mesh->load = false;
}
