/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:10:26 by niduches          #+#    #+#             */
/*   Updated: 2020/06/13 03:05:07 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	quit(t_window *window)
{
	SDL_GL_DeleteContext(window->contex);
	SDL_DestroyWindow(window->win);
	SDL_Quit();
}

void	clear(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void	update_uniform(t_scop *scop)
{
	t_mat4	proj = perspective_matrix(90.0,
(float)scop->win.width / (float)scop->win.height, 0.1, 1000.0);
	t_mat4	view = get_view_matrix(scop->cam);
	glUseProgram(scop->shader);
	glUniformMatrix4fv(glGetUniformLocation(scop->shader, "ProjectionMatrix"), 1,
GL_FALSE, (const GLfloat*)proj.val);
	glUniformMatrix4fv(glGetUniformLocation(scop->shader, "ViewMatrix"), 1,
GL_FALSE, (const GLfloat*)view.val);

	if (scop->light_pos)
	{
		glUniform3fv(glGetUniformLocation(scop->shader, "lightPos"), 1,
		(const GLfloat*)&scop->cam->position);
	}
	else
	{
		glUniform3fv(glGetUniformLocation(scop->shader, "lightPos"), 1,
		(const GLfloat*)&(t_vec3f){0, 0, -3});
	}
	glUniform3fv(glGetUniformLocation(scop->shader, "cameraPos"), 1,
	(const GLfloat*)&scop->cam->position);

	glUniform1f(glGetUniformLocation(scop->shader, "transition"),
(GLfloat)scop->transition);
	glUniform1i(glGetUniformLocation(scop->shader, "use_material"),
(GLint)scop->use_material);
	glUniform1i(glGetUniformLocation(scop->shader, "tex"), scop->tex.type);
	glUseProgram(0);
}

int		main(int ac, char **av)
{
	t_scop		scop;

	if (ac < 2)
		return (0);
	if (!init(&scop, ac, av))
		return (1);
	while (scop.win.open)
	{
		clear();
		update_uniform(&scop);
		update_matrix(&scop.mega);
		draw_mega(&scop.mega, scop.shader, &scop.tex);

		update(&scop, scop.cam);

		if ((scop.transition > 0 && scop.transition_speed < 0) ||
(scop.transition < 1 && scop.transition_speed > 0))
			scop.transition += scop.transition_speed;
		if (scop.obj_move)
			scop.mega.objs[0].rotation.y += 1;
	}
	free(scop.tex.data);
	delete_mega(&scop.mega);
	glDeleteProgram(scop.shader);
	quit(&scop.win);
	return (0);
}
