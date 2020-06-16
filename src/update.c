/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 12:04:06 by niduches          #+#    #+#             */
/*   Updated: 2020/06/16 21:05:50 by niduches         ###   ########.fr       */
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
				mega->objs[i].meshs[j].material += mega->nb_material;
			mega->objs[i].meshs[j].material += dir;
			if (mega->objs[i].meshs[j].material > mega->nb_material)
				mega->objs[i].meshs[j].material -= mega->nb_material + 1;
			++j;
		}
		++i;
	}
}

void	update_event(t_scop *scop)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			scop->win.open = false;
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_w)
				scop->win.key[KEY_W] = false;
			if (event.key.keysym.sym == SDLK_s)
				scop->win.key[KEY_S] = false;
			if (event.key.keysym.sym == SDLK_d)
				scop->win.key[KEY_D] = false;
			if (event.key.keysym.sym == SDLK_a)
				scop->win.key[KEY_A] = false;
			if (event.key.keysym.sym == SDLK_e)
				scop->win.key[KEY_E] = false;
			if (event.key.keysym.sym == SDLK_q)
				scop->win.key[KEY_Q] = false;
			if (event.key.keysym.sym == SDLK_UP)
				scop->win.key[KEY_UP] = false;
			if (event.key.keysym.sym == SDLK_DOWN)
				scop->win.key[KEY_DOWN] = false;
			if (event.key.keysym.sym == SDLK_RIGHT)
				scop->win.key[KEY_RIGHT] = false;
			if (event.key.keysym.sym == SDLK_LEFT)
				scop->win.key[KEY_LEFT] = false;
			if (event.key.keysym.sym == SDLK_SPACE)
				scop->transition_speed *= -1;
			if (event.key.keysym.sym == SDLK_1)
				scop->cam = &scop->cams[0];
			if (event.key.keysym.sym == SDLK_2)
				scop->cam = &scop->cams[1];
			if (event.key.keysym.sym == SDLK_3)
				scop->cam = &scop->cams[2];
			if (event.key.keysym.sym == SDLK_ESCAPE)
				scop->win.open = false;
			if (event.key.keysym.sym == SDLK_u)
			{
				if (scop->use_material == 0)
					scop->use_material = 1;
				else if (scop->use_material == 1)
					scop->use_material = 2;
				else if (scop->use_material == 2)
					scop->use_material = 0;
			}
			if (event.key.keysym.sym == SDLK_i)
				scop->light_pos = !scop->light_pos;
			if (event.key.keysym.sym == SDLK_o)
				scop->obj_move = !scop->obj_move;
			if (event.key.keysym.sym == SDLK_p)
			{
				if (scop->polygon_mode == 0)
				{
					glDisable(GL_CULL_FACE);
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					scop->polygon_mode = 1;
				}
				else if (scop->polygon_mode == 1)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
					scop->polygon_mode = 2;
				}
				else if (scop->polygon_mode == 2)
				{
					glEnable(GL_CULL_FACE);
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					scop->polygon_mode = 0;
				}
			}
			if (event.key.keysym.sym == SDLK_j)
				scop->win.key[KEY_J] = false;
			if (event.key.keysym.sym == SDLK_n)
				scop->win.key[KEY_N] = false;
			if (event.key.keysym.sym == SDLK_k)
				scop->win.key[KEY_K] = false;
			if (event.key.keysym.sym == SDLK_m)
				scop->win.key[KEY_M] = false;
			if (event.key.keysym.sym == SDLK_l)
				scop->win.key[KEY_L] = false;
			if (event.key.keysym.sym == SDLK_COMMA)
				scop->win.key[KEY_COMMA] = false;
			if (event.key.keysym.sym == SDLK_SEMICOLON)
				scop->win.key[KEY_SEMICOLON] = false;
			if (event.key.keysym.sym == SDLK_PERIOD)
				scop->win.key[KEY_PERIOD] = false;
			if (event.key.keysym.sym == SDLK_LSHIFT)
				scop->win.key[KEY_LSHIFT] = false;
			if (event.key.keysym.sym == SDLK_0)
				change_material(&scop->mega, 1);
			if (event.key.keysym.sym == SDLK_9)
				change_material(&scop->mega, -1);
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_w)
				scop->win.key[KEY_W] = true;
			if (event.key.keysym.sym == SDLK_s)
				scop->win.key[KEY_S] = true;
			if (event.key.keysym.sym == SDLK_d)
				scop->win.key[KEY_D] = true;
			if (event.key.keysym.sym == SDLK_a)
				scop->win.key[KEY_A] = true;
			if (event.key.keysym.sym == SDLK_e)
				scop->win.key[KEY_E] = true;
			if (event.key.keysym.sym == SDLK_q)
				scop->win.key[KEY_Q] = true;
			if (event.key.keysym.sym == SDLK_UP)
				scop->win.key[KEY_UP] = true;
			if (event.key.keysym.sym == SDLK_DOWN)
				scop->win.key[KEY_DOWN] = true;
			if (event.key.keysym.sym == SDLK_RIGHT)
				scop->win.key[KEY_RIGHT] = true;
			if (event.key.keysym.sym == SDLK_LEFT)
				scop->win.key[KEY_LEFT] = true;
			if (event.key.keysym.sym == SDLK_j)
				scop->win.key[KEY_J] = true;
			if (event.key.keysym.sym == SDLK_n)
				scop->win.key[KEY_N] = true;
			if (event.key.keysym.sym == SDLK_k)
				scop->win.key[KEY_K] = true;
			if (event.key.keysym.sym == SDLK_m)
				scop->win.key[KEY_M] = true;
			if (event.key.keysym.sym == SDLK_l)
				scop->win.key[KEY_L] = true;
			if (event.key.keysym.sym == SDLK_COMMA)
				scop->win.key[KEY_COMMA] = true;
			if (event.key.keysym.sym == SDLK_SEMICOLON)
				scop->win.key[KEY_SEMICOLON] = true;
			if (event.key.keysym.sym == SDLK_PERIOD)
				scop->win.key[KEY_PERIOD] = true;
			if (event.key.keysym.sym == SDLK_LSHIFT)
				scop->win.key[KEY_LSHIFT] = true;

		}
	}
}

void	update(t_scop *scop, t_camera *cam)
{
	t_vec3f	pos;
	t_vec2f	rot;

	scop->current_time = get_time();
	scop->dt = scop->current_time - scop->last_time;
	scop->last_time = scop->current_time;
	update_event(scop);
	update_camera_vector(cam);
	pos = (t_vec3f){0, 0, 0};
	if (scop->win.key[KEY_W])
		pos.z += 2;
	if (scop->win.key[KEY_S])
		pos.z -= 2;
	if (scop->win.key[KEY_D])
		pos.x -= 2;
	if (scop->win.key[KEY_A])
		pos.x += 2;
	if (scop->win.key[KEY_E])
		pos.y += 2;
	if (scop->win.key[KEY_Q])
		pos.y -= 2;
	move_camera(cam, scop->dt * (scop->win.key[KEY_LSHIFT] ? 2 : 1), pos);
	rot = (t_vec2f){0, 0};
	if (scop->win.key[KEY_UP])
		rot.x += 20;
	if (scop->win.key[KEY_DOWN])
		rot.x -= 20;
	if (scop->win.key[KEY_RIGHT])
		rot.y -= 20;
	if (scop->win.key[KEY_LEFT])
		rot.y += 20;
	rotate_camera(cam, scop->dt * (scop->win.key[KEY_LSHIFT] ? 2 : 1), rot);
	if (scop->win.key[KEY_J])
	{
		move_mega(&scop->mega, (t_vec3f){0.1, 0, 0});
		move_origine_mega(&scop->mega, (t_vec3f){0.1, 0, 0});
	}
	if (scop->win.key[KEY_N])
	{
		move_mega(&scop->mega, (t_vec3f){-0.1, 0, 0});
		move_origine_mega(&scop->mega, (t_vec3f){-0.1, 0, 0});
	}
	if (scop->win.key[KEY_K])
	{
		move_mega(&scop->mega, (t_vec3f){0, 0.1, 0});
		move_origine_mega(&scop->mega, (t_vec3f){0, 0.1, 0});
	}
	if (scop->win.key[KEY_M])
	{
		move_mega(&scop->mega, (t_vec3f){0, -0.1, 0});
		move_origine_mega(&scop->mega, (t_vec3f){0, -0.1, 0});
	}
	if (scop->win.key[KEY_L])
	{
		move_mega(&scop->mega, (t_vec3f){0, 0, 0.1});
		move_origine_mega(&scop->mega, (t_vec3f){0, 0, 0.1});
	}
	if (scop->win.key[KEY_COMMA])
	{
		move_mega(&scop->mega, (t_vec3f){0, 0, -0.1});
		move_origine_mega(&scop->mega, (t_vec3f){0, 0, -0.1});
	}
	if (scop->win.key[KEY_SEMICOLON])
		scale_mega(&scop->mega, (t_vec3f){0.02, 0.02, 0.02});
	if (scop->win.key[KEY_PERIOD])
		scale_mega(&scop->mega, (t_vec3f){-0.02, -0.02, -0.02});
}
