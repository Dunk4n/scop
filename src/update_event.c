/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:15:00 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 17:47:59 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void			change_material(t_mega_obj *mega, int dir)
{
	uint	i;
	uint	j;

	i = 0;
	while (i < mega->nb_obj)
	{
		j = 0;
		while (j < mega->objs[i].nb_mesh)
		{
			if (dir < 0 && (uint)(-dir) > mega->objs[i].meshs[j].material)
				mega->objs[i].meshs[j].material += mega->nb_material + 1;
			mega->objs[i].meshs[j].material += dir;
			if (mega->objs[i].meshs[j].material > mega->nb_material)
				mega->objs[i].meshs[j].material -= mega->nb_material + 1;
			++j;
		}
		++i;
	}
}

static const int	g_keycode_sdl[NB_KEY] =
{
	SDLK_w, SDLK_s, SDLK_d, SDLK_a, SDLK_e, SDLK_q, SDLK_UP, SDLK_DOWN,
	SDLK_RIGHT, SDLK_LEFT, SDLK_j, SDLK_n, SDLK_k, SDLK_m, SDLK_l, SDLK_COMMA,
	SDLK_SEMICOLON, SDLK_PERIOD, SDLK_LSHIFT,
};

static void			update_keyup_camera(t_scop *scop, SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_1)
		scop->cam = &scop->cams[0];
	if (event->key.keysym.sym == SDLK_2)
		scop->cam = &scop->cams[1];
	if (event->key.keysym.sym == SDLK_3)
		scop->cam = &scop->cams[2];
	if (event->key.keysym.sym == SDLK_p)
	{
		scop->polygon_mode = (scop->polygon_mode + 1) % 3;
		if (scop->polygon_mode == 1)
		{
			glDisable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else if (scop->polygon_mode == 2)
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		else if (scop->polygon_mode == 0)
		{
			if (!scop->explo)
				glEnable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}

static void			update_keyup_material(t_scop *scop, SDL_Event *event)
{
	if (event->key.keysym.sym == SDLK_SPACE)
		scop->transition_speed *= -1;
	if (event->key.keysym.sym == SDLK_u)
		scop->use_material = (scop->use_material + 1) % 3;
	if (event->key.keysym.sym == SDLK_i)
		scop->light_pos = !scop->light_pos;
	if (event->key.keysym.sym == SDLK_o)
		scop->obj_move = !scop->obj_move;
	if (event->key.keysym.sym == SDLK_0)
		change_material(&scop->mega, 1);
	if (event->key.keysym.sym == SDLK_9)
		change_material(&scop->mega, -1);
	if (event->key.keysym.sym == SDLK_h)
		scop->normal = !scop->normal;
}

void				update_keyup(t_scop *scop, SDL_Event *event)
{
	uint	i;

	i = 0;
	while (i < NB_KEY)
	{
		if (event->key.keysym.sym == g_keycode_sdl[i])
			scop->win.key[i] = false;
		++i;
	}
	if (event->key.keysym.sym == SDLK_ESCAPE)
		scop->win.open = false;
	if (event->key.keysym.sym == SDLK_y)
	{
		scop->explo = !scop->explo;
		if (!scop->polygon_mode && !scop->explo)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);
	}
	update_keyup_camera(scop, event);
	update_keyup_material(scop, event);
}

void				update_keydown(t_scop *scop, SDL_Event *event)
{
	uint	i;

	i = 0;
	while (i < NB_KEY)
	{
		if (event->key.keysym.sym == g_keycode_sdl[i])
			scop->win.key[i] = true;
		++i;
	}
}
