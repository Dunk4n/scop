/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 15:17:31 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 22:51:18 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	update_matrix(t_mega_obj *mega)
{
	uint	i;
	uint	j;

	i = 0;
	while (i < mega->nb_obj)
	{
		update_obj_matrix(&mega->objs[i]);
		j = 0;
		while (j < mega->objs[i].nb_mesh)
		{
			update_mesh_matrix(&mega->objs[i].meshs[j],
			mega->objs[i].model_matrix);
			++j;
		}
		++i;
	}
}

void	update_display(t_scop *scop)
{
	SDL_GL_SwapWindow(scop->win.win);
	clear();
	update(scop, scop->cam);
	update_matrix(&scop->mega);
	update_uniform(scop, scop->shader);
	draw_mega(&scop->mega, scop->shader);
	if (scop->normal)
	{
		update_uniform(scop, scop->shader_normal);
		draw_mega(&scop->mega, scop->shader_normal);
	}
	if ((scop->transition > 0 && scop->transition_speed < 0) ||
(scop->transition < 1 && scop->transition_speed > 0))
		scop->transition += scop->transition_speed * scop->dt;
	if (scop->transition < 0)
		scop->transition = 0;
	if (scop->transition > 1)
		scop->transition = 1;
	if (scop->obj_move)
		rotate_mega(&scop->mega, (t_vec3f){0, 20 * scop->dt, 0});
}

void	update_uniform(t_scop *scop, GLuint shader)
{
	t_mat4	proj;
	t_mat4	view;

	proj = perspective_matrix(80.0,
(float)scop->win.width / (float)scop->win.height, 0.1, 1000.0);
	view = get_view_matrix(scop->cam);
	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "ProjectionMatrix"), 1,
GL_FALSE, (const GLfloat*)proj.val);
	glUniformMatrix4fv(glGetUniformLocation(shader, "ViewMatrix"), 1,
GL_FALSE, (const GLfloat*)view.val);
	glUniform3fv(glGetUniformLocation(shader, "lightPos"), 1, (scop->light_pos
) ? (const GLfloat*)&scop->cam->position : (const GLfloat*)&(t_vec3f){0, 0, 3});
	glUniform3fv(glGetUniformLocation(shader, "cameraPos"), 1,
	(const GLfloat*)&scop->cam->position);
	glUniform1f(glGetUniformLocation(shader, "transition"),
(GLfloat)scop->transition);
	glUniform1f(glGetUniformLocation(shader, "explosion"), scop->explo ?
(GLfloat)scop->last_time : (GLfloat)(-1.0));
	glUniform1i(glGetUniformLocation(shader, "use_material"),
(GLint)scop->use_material);
	glUniform1i(glGetUniformLocation(shader, "material.diffuse_tex"), 0);
	glUniform1i(glGetUniformLocation(shader, "material.specular_tex"), 1);
	glUseProgram(0);
}
