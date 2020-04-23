/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:10:26 by niduches          #+#    #+#             */
/*   Updated: 2020/04/22 15:32:29 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	quit(t_window window)
{
	SDL_GL_DeleteContext(window.contex);
	SDL_DestroyWindow(window.win);
	SDL_Quit();
}

void	clear(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void	update(t_window *win)
{
	SDL_Event	event;

	SDL_GL_SwapWindow(win->win);
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			win->open = false;
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				win->open = false;
		}
	}
}

t_vertex	array[] = {
	{{-0.5, -0.5, 0},	{1.0, 0.0, 0.0},	{0.0, 1.0}},
	{{0.5, -0.5, 0},	{0.0, 1.0, 0.0},	{1.0, 1.0}},
	{{-0.5, 0.5, 0},	{0.0, 0.0, 1.0},	{0.0, 0.0}},
	{{0.5, 0.5, 0},	{1.0, 0.0, 0.0},	{1.0, 0.0}}
};

unsigned int	idx[] = {
	0, 1, 2,
	1, 3, 2};

void	draw(GLuint arayObj, GLuint shader)
{
	glUseProgram(shader);
	glBindVertexArray(arayObj);

	glDrawElements(GL_TRIANGLES, sizeof(idx) / sizeof(idx[0]), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}

int		main(void)
{
	t_window	win;

	win = init("test", 800, 600);
	if (!win.open)
		return (1);

	t_mesh	mesh = get_mesh("resources/cube.obj");
	if (!mesh.array_obj)
		return (0);
	GLuint	id_shader = get_shader(
"resources/shader/basicShader.vs", "resources/shader/basicShader.fs");
	if (!id_shader)
	{
		delete_mesh(&mesh);
		quit(win);
		return (0);
	}
	//TODO texture with parser
	//TODO material with parser
	//TODO object
	t_camera	cam = init_cam();
	while (win.open)
	{
		clear();
		update_mesh_uniform(&mesh, id_shader);

		t_mat4	proj = perspective_matrix(90, (float)win.width / (float)win.height, 0.1, 1000);
		t_mat4	view = get_view_matrix(&cam);
		glUseProgram(id_shader);
		glUniformMatrix4fv(glGetUniformLocation(id_shader, "ProjectionMatrix"), 1, GL_FALSE, (const GLfloat*)proj.val);
		glUniformMatrix4fv(glGetUniformLocation(id_shader, "ViewMatrix"), 1, GL_FALSE, (const GLfloat*)view.val);
		glUseProgram(0);

		draw(mesh.array_obj, id_shader);
		update(&win);
	}
	glDeleteProgram(id_shader);
	delete_mesh(&mesh);
	quit(win);
	return (0);
}
