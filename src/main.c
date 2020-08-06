/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:10:26 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 22:36:02 by niduches         ###   ########.fr       */
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

void	delete_all(t_scop *scop)
{
	delete_mega(&scop->mega);
	glDeleteProgram(scop->shader);
	glDeleteProgram(scop->shader_normal);
	quit(&scop->win);
}

void	clear(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

double	get_time(void)
{
	return (SDL_GetTicks() * 0.001);
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
	update_matrix(&scop.mega);
	update_uniform(&scop, scop.shader);
	draw_mega(&scop.mega, scop.shader);
	while (scop.win.open)
	{
		if (get_time() - scop.last_time >= FRAMES_RATE)
			update_display(&scop);
	}
	delete_all(&scop);
	return (0);
}
