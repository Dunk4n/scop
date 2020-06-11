/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 17:28:59 by niduches          #+#    #+#             */
/*   Updated: 2020/06/11 18:04:31 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	load_material(t_material *material, GLuint shader)
{
	t_material	mat;

	if (material)
		mat = *material;
	else
	{
		mat.ambient = (t_vec3f){1, 1, 1};
		mat.diffuse = (t_vec3f){0, 0, 0};
		mat.specular = (t_vec3f){0, 0, 0};
		mat.shininess = 1;
		mat.transparency = 1;
	}
	glUniform3fv(glGetUniformLocation(shader, "material.ambient"), 1,
	(const GLfloat*)&mat.ambient);
	glUniform3fv(glGetUniformLocation(shader, "material.diffuse"), 1,
	(const GLfloat*)&mat.diffuse);
	glUniform3fv(glGetUniformLocation(shader, "material.specular"), 1,
	(const GLfloat*)&mat.specular);
	glUniform1f(glGetUniformLocation(shader, "material.shininess"),
	mat.shininess);
	glUniform1f(glGetUniformLocation(shader, "material.transparency"),
	mat.transparency);
}

static void	draw_mesh(t_mega_obj *mega, t_mesh *mesh, GLuint shader)
{
	if (!mesh->load)
		return ;
	glUseProgram(shader);
	glBindVertexArray(mesh->array_obj);
	if (mesh->material && mesh->material <= mega->nb_material)
		load_material(&mega->materials[mesh->material - 1], shader);
	else
		load_material(NULL, shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "ModelMatrix"),
1, GL_TRUE, (const GLfloat*)mesh->model_matrix.val);
	glDrawElements(GL_TRIANGLES, mesh->nb_index, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

static void	draw_obj(t_mega_obj *mega, t_obj *obj, GLuint shader)
{
	uint	i;

	if (!obj->load)
		return ;
	i = 0;
	while (i < obj->nb_mesh)
		draw_mesh(mega, &obj->meshs[i++], shader);
}

void	draw_mega(t_mega_obj *mega, GLuint shader, t_texture *tex)
{
	uint	i;

	bind_texture(tex, 0);
	i = 0;
	while (i < mega->nb_obj)
		draw_obj(mega, &mega->objs[i++], shader);
	unbind_texture(tex);
}
