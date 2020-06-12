/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 12:04:06 by niduches          #+#    #+#             */
/*   Updated: 2020/06/12 04:05:51 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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
				scop->use_material = !scop->use_material;
			if (event.key.keysym.sym == SDLK_i)
				scop->light_pos = !scop->light_pos;
			if (event.key.keysym.sym == SDLK_o)
				scop->obj_move = !scop->obj_move;
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
		}
	}
}

void	update(t_scop *scop, t_camera *cam)
{
	SDL_GL_SwapWindow(scop->win.win);
	update_event(scop);
	update_camera_vector(cam);
	//TODO make camera movement
	if (scop->win.key[KEY_W])
		cam->position = add_vector(cam->position, mult_vector(cam->front, cam->movement_speed));
	if (scop->win.key[KEY_S])
		cam->position = sub_vector(cam->position, mult_vector(cam->front, cam->movement_speed));
	if (scop->win.key[KEY_D])
		cam->position = sub_vector(cam->position, mult_vector(cam->right, cam->movement_speed));
	if (scop->win.key[KEY_A])
		cam->position = add_vector(cam->position, mult_vector(cam->right, cam->movement_speed));
	if (scop->win.key[KEY_E])
		cam->position = add_vector(cam->position, mult_vector(cam->up, cam->movement_speed));
	if (scop->win.key[KEY_Q])
		cam->position = sub_vector(cam->position, mult_vector(cam->up, cam->movement_speed));
	if (scop->win.key[KEY_UP] && cam->pitch + 1 <= 90)
		cam->pitch += 1;
	if (scop->win.key[KEY_DOWN] && cam->pitch - 1 >= -90)
		cam->pitch -= 1;
	if (scop->win.key[KEY_RIGHT])
		cam->yaw -= 1;
	if (scop->win.key[KEY_LEFT])
		cam->yaw += 1;
}
