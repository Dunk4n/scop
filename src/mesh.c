/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 23:00:37 by niduches          #+#    #+#             */
/*   Updated: 2020/04/25 14:05:31 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	update_model_matrix(t_mesh *mesh)
{
	mesh->model_matrix = translation_matrix(identity_matrix(), mesh->origin);
	mesh->model_matrix =
rotation_matrix(mesh->model_matrix, (mesh->rotation.x * M_PI) / 180.0, (t_vec3f){1, 0, 0});
	mesh->model_matrix =
rotation_matrix(mesh->model_matrix, (mesh->rotation.y * M_PI) / 180.0, (t_vec3f){0, 1, 0});
	mesh->model_matrix =
rotation_matrix(mesh->model_matrix, (mesh->rotation.z * M_PI) / 180.0, (t_vec3f){0, 0, 1});
	mesh->model_matrix = translation_matrix(mesh->model_matrix, sub_vec3f(mesh->position, mesh->origin));
	mesh->model_matrix = scale_matrix(mesh->model_matrix, mesh->scale);
}

t_mesh	get_mesh(const char *name)
{
	(void)name;
	t_mesh	mesh;

	mesh.position = (t_vec3f){0, 0, 0};
	mesh.origin = (t_vec3f){0, 0, 0};
	mesh.rotation = (t_vec3f){0, 0, 0};
	mesh.scale = (t_vec3f){1, 1, 1};
	update_model_matrix(&mesh);


	//TODO rm that
	mesh.nb_vertex = sizeof(array) / sizeof(t_vertex);
	mesh.nb_index = sizeof(idx) / sizeof(unsigned int);
	//
	glGenVertexArrays(1, &mesh.array_obj);
	glBindVertexArray(mesh.array_obj);

	glGenBuffers(1, &mesh.array_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.array_buffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.nb_vertex * sizeof(t_vertex), array, GL_STATIC_DRAW);

	glGenBuffers(1, &mesh.array_buffer_index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.array_buffer_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.nb_index * sizeof(unsigned int), idx, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
(GLvoid*)offsetof(t_vertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
(GLvoid*)offsetof(t_vertex, normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
(GLvoid*)offsetof(t_vertex, texcoord));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	return (mesh);
}

void	update_mesh_uniform(t_mesh *mesh, GLuint shader)
{
	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "ModelMatrix"),
1, GL_FALSE, (const GLfloat*)mesh->model_matrix.val);
	glUseProgram(0);
}

void	init_mesh(t_mesh *mesh)
{
	mesh->position = (t_vec3f){0, 0, 0};
	mesh->origin = (t_vec3f){0, 0, 0};
	mesh->rotation = (t_vec3f){0, 0, 0};
	mesh->scale = (t_vec3f){0, 0, 0};
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
