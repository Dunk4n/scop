/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:10:26 by niduches          #+#    #+#             */
/*   Updated: 2020/10/09 18:45:52 by niduches         ###   ########.fr       */
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

char const *g_usage =
"./scop [--color] [--position] filename.obj ...\n\nCOMMAND\n\n\
Camera:\n\t'w' and 's' move the camera front or back\n\
\t'd' and 'a' move the camera right or left\n\
\t'e' and 'q' move the camera up or down\n\
\t'UP' and 'DOWN' rotate the camera up or down\n\
\t'RIGHT' and 'LEFT' rotate the camera right or left\n\
\t'1', '2' and '3' switch between 3 different cameras\n\nTransformation:\n\
\t'o' set or unset model rotation\n\t'j' and 'n' move the model on the x axis\n\
\t'k' and 'm' move the model on the y axis\n\
\t'l' and ',' move the model on the z axis\n\
\t';' and '.' change the model size\n\
\t'shift' + 'j' or 'n' rotate the model on the x axis\n\
\t'shift' + 'k' or 'm' rotate the model on the y axis\n\
\t'shift' + 'l' or ',' rotate the model on the z axis\n\nDisplay:\n\
\t'space' switch between color and texture\n\
\t'p' switch polygon mode between fill, line, point\n\
\t'u' switch mode between all, material, color/texture\n\
\t'0' and '9' change the material of the model\n\
\t'h' set or unset normal vector mode\n\nOther:\n\
\t'i' switch the position of the light from the origin to the camera\n\
\t'y' set or unset destruction mode\n";

int		main(int ac, char **av)
{
	t_scop		scop;

	if (ac < 2)
	{
		ft_printf(g_usage);
		return (0);
	}
	if (!init(&scop, ac, av))
	{
		ft_printf(g_usage);
		return (0);
	}
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
