/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 12:04:06 by niduches          #+#    #+#             */
/*   Updated: 2020/06/08 19:56:36 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	update_event(t_window *win, float *vitesse_transition)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			win->open = false;
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_w)
				win->key[KEY_W] = false;
			if (event.key.keysym.sym == SDLK_s)
				win->key[KEY_S] = false;
			if (event.key.keysym.sym == SDLK_d)
				win->key[KEY_D] = false;
			if (event.key.keysym.sym == SDLK_a)
				win->key[KEY_A] = false;
			if (event.key.keysym.sym == SDLK_e)
				win->key[KEY_E] = false;
			if (event.key.keysym.sym == SDLK_q)
				win->key[KEY_Q] = false;
			if (event.key.keysym.sym == SDLK_UP)
				win->key[KEY_UP] = false;
			if (event.key.keysym.sym == SDLK_DOWN)
				win->key[KEY_DOWN] = false;
			if (event.key.keysym.sym == SDLK_RIGHT)
				win->key[KEY_RIGHT] = false;
			if (event.key.keysym.sym == SDLK_LEFT)
				win->key[KEY_LEFT] = false;
			if (event.key.keysym.sym == SDLK_SPACE)
				*vitesse_transition *= -1;
			if (event.key.keysym.sym == SDLK_ESCAPE)
				win->open = false;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_w)
				win->key[KEY_W] = true;
			if (event.key.keysym.sym == SDLK_s)
				win->key[KEY_S] = true;
			if (event.key.keysym.sym == SDLK_d)
				win->key[KEY_D] = true;
			if (event.key.keysym.sym == SDLK_a)
				win->key[KEY_A] = true;
			if (event.key.keysym.sym == SDLK_e)
				win->key[KEY_E] = true;
			if (event.key.keysym.sym == SDLK_q)
				win->key[KEY_Q] = true;
			if (event.key.keysym.sym == SDLK_UP)
				win->key[KEY_UP] = true;
			if (event.key.keysym.sym == SDLK_DOWN)
				win->key[KEY_DOWN] = true;
			if (event.key.keysym.sym == SDLK_RIGHT)
				win->key[KEY_RIGHT] = true;
			if (event.key.keysym.sym == SDLK_LEFT)
				win->key[KEY_LEFT] = true;
		}
	}
}

void	update(t_window *win, t_camera *cam, float *vitesse_transition)
{
	SDL_GL_SwapWindow(win->win);
	update_event(win, vitesse_transition);
	update_camera_vector(cam);
	//TODO make camera movement
	if (win->key[KEY_W])
		cam->position = add_vector(cam->position, mult_vector(cam->front, cam->movement_speed));
	if (win->key[KEY_S])
		cam->position = sub_vector(cam->position, mult_vector(cam->front, cam->movement_speed));
	if (win->key[KEY_D])
		cam->position = sub_vector(cam->position, mult_vector(cam->right, cam->movement_speed));
	if (win->key[KEY_A])
		cam->position = add_vector(cam->position, mult_vector(cam->right, cam->movement_speed));
	if (win->key[KEY_E])
		cam->position = add_vector(cam->position, mult_vector(cam->up, cam->movement_speed));
	if (win->key[KEY_Q])
		cam->position = sub_vector(cam->position, mult_vector(cam->up, cam->movement_speed));
	if (win->key[KEY_UP] && cam->pitch + 1 <= 90)
		cam->pitch += 1;
	if (win->key[KEY_DOWN] && cam->pitch - 1 >= -90)
		cam->pitch -= 1;
	if (win->key[KEY_RIGHT])
		cam->yaw -= 1;
	if (win->key[KEY_LEFT])
		cam->yaw += 1;
}
