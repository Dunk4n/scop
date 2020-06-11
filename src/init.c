/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 14:32:39 by niduches          #+#    #+#             */
/*   Updated: 2020/06/11 05:11:59 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "scop.h"

static int		set_sdl(char *name, int width, int height, t_window *window)
{
	window->open = false;
	if (!name || SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return (0);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	window->win = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED,
SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (!window->win)
		return (0);
	window->contex = SDL_GL_CreateContext(window->win);
	if (!window->contex)
	{
		SDL_DestroyWindow(window->win);
		window->win = NULL;
		return (0);
	}
	return (1);
}

static void		enable_gl_option(void)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glClearColor(0.5, 0, 0.8, 1);
}

static t_window	init_window(char *name, int width, int height)
{
	t_window	window;
	uint		i;

	window.width = width;
	window.height = height;
	if (!set_sdl(name, width, height, &window) || glewInit() != GLEW_OK)
	{
		if (window.contex)
			SDL_GL_DeleteContext(window.contex);
		if (window.win)
			SDL_DestroyWindow(window.win);
		window.win = NULL;
		SDL_Quit();
		return (window);
	}
	enable_gl_option();
	window.open = true;
	i = 0;
	while (i < NB_KEY)
		window.key[i++] = false;
	return (window);
}

static void		init_value(t_scop *scop)
{
	scop->transition = 0;
	scop->transition_speed = -0.01;
	scop->mega.objs = NULL;
	scop->mega.materials = NULL;
	scop->mega.nb_obj = 0;
	scop->mega.nb_material = 0;
}

int				init(t_scop *scop, const char *filename)
{
	srand(time(NULL));
	scop->win = init_window("scop", 1920, 1080);
	if (!scop->win.open)
		return (0);
	if (!(scop->shader = get_shader(
"resources/shader/basicShader.vs", "resources/shader/basicShader.fs")))
	{
		quit(&scop->win);
		return (0);
	}
	scop->cam = init_cam();
	init_value(scop);
	scop->tex = get_bmp("resources/gri.bmp", GL_TEXTURE_2D);
	//TODO material with parser
	if (!scop->tex.data || !load_obj(&scop->mega, filename))
	{
		free(scop->tex.data);
		scop->tex.data = NULL;
		delete_mega(&scop->mega);
		glDeleteProgram(scop->shader);
		quit(&scop->win);
		return (0);
	}
	preprocess_mega(&scop->mega);
	load_gl_mega(&scop->mega);
	load_texture(&scop->tex);
	return (1);
}
