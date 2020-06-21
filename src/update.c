/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 12:04:06 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 01:39:35 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	change_material(t_mega_obj *mega, int dir)
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

static const int	g_keycode_sdl[NB_KEY] = {
SDLK_w, SDLK_s, SDLK_d, SDLK_a, SDLK_e, SDLK_q, SDLK_UP, SDLK_DOWN, SDLK_RIGHT,
SDLK_LEFT, SDLK_j, SDLK_n, SDLK_k, SDLK_m, SDLK_l, SDLK_COMMA, SDLK_SEMICOLON,
SDLK_PERIOD, SDLK_LSHIFT,
};

void	update_keydown(t_scop *scop, SDL_Event *event)
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

void	update_keyup_camera(t_scop *scop, SDL_Event *event)
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

void	update_keyup_material(t_scop *scop, SDL_Event *event)
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

void	update_keyup(t_scop *scop, SDL_Event *event)
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

void	update_event(t_scop *scop)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			scop->win.open = false;
		else if (event.type == SDL_KEYUP)
			update_keyup(scop, &event);
		else if (event.type == SDL_KEYDOWN)
			update_keydown(scop, &event);
	}
}

void	update_camera(t_scop *scop, t_camera *cam)
{
	t_vec3f	pos;
	t_vec2f	rot;

	update_camera_vector(cam);
	pos = (t_vec3f){0, 0, 0};
	if (scop->win.key[KEY_W])
		pos.z += 50 * scop->dt;
	if (scop->win.key[KEY_S])
		pos.z -= 50 * scop->dt;
	if (scop->win.key[KEY_D])
		pos.x += 50 * scop->dt;
	if (scop->win.key[KEY_A])
		pos.x -= 50 * scop->dt;
	if (scop->win.key[KEY_E])
		pos.y += 50 * scop->dt;
	if (scop->win.key[KEY_Q])
		pos.y -= 50 * scop->dt;
	move_camera(cam, scop->dt * (scop->win.key[KEY_LSHIFT] ? 2 : 1), pos);
	rot = (t_vec2f){0, 0};
	if (scop->win.key[KEY_UP] || scop->win.key[KEY_DOWN])
		rot.x = scop->win.key[KEY_UP] ? 1 : -1;
	if (scop->win.key[KEY_RIGHT] || scop->win.key[KEY_LEFT])
		rot.y = scop->win.key[KEY_RIGHT] ? 1 : -1;
	rotate_camera(cam, scop->dt * (scop->win.key[KEY_LSHIFT] ? 2 : 1), rot);
}

void	update_rotate(t_scop *scop)
{
	if (scop->win.key[KEY_J] && scop->win.key[KEY_LSHIFT])
		rotate_mega(&scop->mega, (t_vec3f){40 * scop->dt, 0, 0});
	if (scop->win.key[KEY_N] && scop->win.key[KEY_LSHIFT])
		rotate_mega(&scop->mega, (t_vec3f){-40 * scop->dt, 0, 0});
	if (scop->win.key[KEY_K] && scop->win.key[KEY_LSHIFT])
		rotate_mega(&scop->mega, (t_vec3f){0, 40 * scop->dt, 0});
	if (scop->win.key[KEY_M] && scop->win.key[KEY_LSHIFT])
		rotate_mega(&scop->mega, (t_vec3f){0, -40 * scop->dt, 0});
	if (scop->win.key[KEY_L] && scop->win.key[KEY_LSHIFT])
		rotate_mega(&scop->mega, (t_vec3f){0, 0, 40 * scop->dt});
	if (scop->win.key[KEY_COMMA] && scop->win.key[KEY_LSHIFT])
		rotate_mega(&scop->mega, (t_vec3f){0, 0, -40 * scop->dt});
	if (scop->win.key[KEY_SEMICOLON])
		scale_mega(&scop->mega,
		(t_vec3f){0.1 * scop->dt, 0.1 * scop->dt, 0.1 * scop->dt});
	if (scop->win.key[KEY_PERIOD])
		scale_mega(&scop->mega,
		(t_vec3f){-0.1 * scop->dt, -0.1 * scop->dt, -0.1 * scop->dt});
}

void	update(t_scop *scop, t_camera *cam)
{
	scop->current_time = get_time();
	scop->dt = scop->current_time - scop->last_time;
	scop->last_time = scop->current_time;
	update_event(scop);
	update_camera(scop, cam);
	if (scop->win.key[KEY_J] && !scop->win.key[KEY_LSHIFT])
		move_and_origine_mega(&scop->mega, (t_vec3f){5 * scop->dt, 0, 0});
	if (scop->win.key[KEY_N] && !scop->win.key[KEY_LSHIFT])
		move_and_origine_mega(&scop->mega, (t_vec3f){-5 * scop->dt, 0, 0});
	if (scop->win.key[KEY_K] && !scop->win.key[KEY_LSHIFT])
		move_and_origine_mega(&scop->mega, (t_vec3f){0, 5 * scop->dt, 0});
	if (scop->win.key[KEY_M] && !scop->win.key[KEY_LSHIFT])
		move_and_origine_mega(&scop->mega, (t_vec3f){0, -5 * scop->dt, 0});
	if (scop->win.key[KEY_L] && !scop->win.key[KEY_LSHIFT])
		move_and_origine_mega(&scop->mega, (t_vec3f){0, 0, 5 * scop->dt});
	if (scop->win.key[KEY_COMMA] && !scop->win.key[KEY_LSHIFT])
		move_and_origine_mega(&scop->mega, (t_vec3f){0, 0, -5 * scop->dt});
	update_rotate(scop);
}
