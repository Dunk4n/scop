/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 12:04:06 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 17:16:30 by niduches         ###   ########.fr       */
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
