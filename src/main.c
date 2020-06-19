/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:10:26 by niduches          #+#    #+#             */
/*   Updated: 2020/06/19 00:51:13 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
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

double	get_time(void)
{
	return (SDL_GetTicks() * 0.001);
}

void	update_uniform(t_scop *scop)
{
	t_mat4	proj = perspective_matrix(80.0,
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
		(const GLfloat*)&(t_vec3f){0, 0, 3});
	}
	glUniform3fv(glGetUniformLocation(scop->shader, "cameraPos"), 1,
	(const GLfloat*)&scop->cam->position);

	glUniform1f(glGetUniformLocation(scop->shader, "transition"),
(GLfloat)scop->transition);
	if (scop->explo)
		glUniform1f(glGetUniformLocation(scop->shader, "explosion"), (GLfloat)scop->last_time);
	else
		glUniform1f(glGetUniformLocation(scop->shader, "explosion"), (GLfloat)(-1.0));
	glUniform1i(glGetUniformLocation(scop->shader, "use_material"),
(GLint)scop->use_material);
	glUniform1i(glGetUniformLocation(scop->shader, "material.diffuse_tex"), 0);
	glUniform1i(glGetUniformLocation(scop->shader, "material.specular_tex"), 1);
	glUseProgram(0);
}

int		main(int ac, char **av)
{
	t_scop		scop;

	if (ac < 2)
		return (0);
	if (!init(&scop, ac, av))
		return (0);
	clear();
	SDL_GL_SwapWindow(scop.win.win);
	clear();
	update(&scop, scop.cam);
	update_uniform(&scop);
	update_matrix(&scop.mega);

	draw_mega(&scop.mega, scop.shader);
	while (scop.win.open)
	{
		if (get_time() - scop.last_time > FRAMES_RATE)
		{
			SDL_GL_SwapWindow(scop.win.win);
			clear();

			update(&scop, scop.cam);
			//printf("%f\n", 1 / scop.dt);
			update_uniform(&scop);
			update_matrix(&scop.mega);

			draw_mega(&scop.mega, scop.shader);

			if ((scop.transition > 0 && scop.transition_speed < 0) ||
(scop.transition < 1 && scop.transition_speed > 0))
				scop.transition += scop.transition_speed * scop.dt;
			if (scop.transition < 0)
				scop.transition = 0;
			if (scop.transition > 1)
				scop.transition = 1;
			if (scop.obj_move)
				rotate_mega(&scop.mega, (t_vec3f){0, 20 * scop.dt, 0});
		}
	}
	delete_mega(&scop.mega);
	glDeleteProgram(scop.shader);
	quit(&scop.win);
	return (0);
}
