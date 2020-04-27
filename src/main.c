/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:10:26 by niduches          #+#    #+#             */
/*   Updated: 2020/04/27 15:41:47 by niduches         ###   ########.fr       */
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

void	main_update_uniform(t_window win, t_camera cam, GLuint shader,
float transition, t_texture *tex)
{
	t_mat4	proj = perspective_matrix(90, (float)win.width / (float)win.height, 0.1, 1000);
	t_mat4	view = get_view_matrix(&cam);
	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "ProjectionMatrix"), 1,
GL_FALSE, (const GLfloat*)proj.val);
	glUniformMatrix4fv(glGetUniformLocation(shader, "ViewMatrix"), 1,
GL_FALSE, (const GLfloat*)view.val);
	glUniform1f(glGetUniformLocation(shader, "transition"),
(GLfloat)transition);
	glUniform1i(glGetUniformLocation(shader, "tex"), tex->type);
	glUseProgram(0);
}

int		main(void)
{
	t_window	win;
 	t_mega_obj	mega;

	win = init("test", 1920, 1080);
	if (!win.open)
		return (1);
	GLuint	shader = get_shader(
"resources/shader/basicShader.vs", "resources/shader/basicShader.fs");
	if (!shader)
	{
		quit(&win);
		return (0);
	}
	//TODO material with parser
	t_camera	cam = init_cam();

	//MEGA
	mega.objs = NULL;
	mega.materials = NULL;
	mega.nb_obj = 0;
	mega.nb_material = 0;
	if (!load_obj(&mega, "resources/cube.obj"))
	{
		printf("a\n");
		delete_mega(&mega);
		glDeleteProgram(shader);
		quit(&win);
		return (0);
	}
	//
	load_gl_mega(&mega);
	t_texture tex = get_bmp("gri.bmp", GL_TEXTURE_2D);
	if (!tex.data)
	{
		delete_mega(&mega);
		glDeleteProgram(shader);
		quit(&win);
		return (0);
	}
	load_texture(&tex);

//	mega.objs[0].meshs[1].scale = (t_vec3f){0.1, 0.1, 0.1};
//	mega.objs[0].meshs[1].position.x = 1;
	float	transition = 0;
	float	vitesse_transition = -8;
	while (win.open)
	{
		clear();
		main_update_uniform(win, cam, shader, transition, &tex);

		//TODO make mega update matrix
		update_obj_matrix(&mega.objs[0]);
		update_mesh_matrix(&mega.objs[0].meshs[0], mega.objs[0].model_matrix);
//		update_mesh_matrix(&mega.objs[0].meshs[1], mega.objs[0].model_matrix);

		draw_mega(&mega, shader, &tex);
		update(&win, &cam, &vitesse_transition);

		if ((transition > 0 && vitesse_transition < 0) ||
(transition < 1920 && vitesse_transition > 0))
			transition += vitesse_transition;
	}
	delete_mega(&mega);
	glDeleteProgram(shader);
	quit(&win);
	return (0);
}
