/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 17:28:59 by niduches          #+#    #+#             */
/*   Updated: 2020/06/09 17:52:26 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	draw_mesh(t_mesh *mesh, GLuint shader)
{
	if (!mesh->load)
		return ;
	glUseProgram(shader);
	glBindVertexArray(mesh->array_obj);
	glUniformMatrix4fv(glGetUniformLocation(shader, "ModelMatrix"),
1, GL_TRUE, (const GLfloat*)mesh->model_matrix.val);
	glDrawElements(GL_TRIANGLES, mesh->nb_index, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void	draw_obj(t_obj *obj, GLuint shader)
{
	uint	i;

	if (!obj->load)
		return ;
	i = 0;
	while (i < obj->nb_mesh)
		draw_mesh(&obj->meshs[i++], shader);
}

void	draw_mega(t_mega_obj *mega, GLuint shader, t_texture *tex)
{
	uint	i;

	bind_texture(tex, 0);
	i = 0;
	while (i < mega->nb_obj)
		draw_obj(&mega->objs[i++], shader);
	unbind_texture(tex);
}
