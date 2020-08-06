/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 14:32:39 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 22:59:20 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "scop.h"

static void	init_value(t_scop *scop)
{
	scop->cams[0] = init_cam();
	scop->cams[1] = init_cam();
	scop->cams[2] = init_cam();
	scop->cam = &scop->cams[0];
	scop->transition = 0;
	scop->transition_speed = -0.4;
	scop->mega.objs = NULL;
	scop->mega.materials = NULL;
	scop->mega.nb_obj = 0;
	scop->mega.nb_material = 0;
	scop->use_material = 0;
	scop->light_pos = false;
	scop->obj_move = true;
	scop->polygon_mode = 0;
	scop->current_time = 0;
	scop->last_time = 0;
	scop->dt = 0;
	scop->explo = 0;
	scop->normal = 0;
}

int			init_all_obj_file(t_scop *scop, int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		if (!load_obj(&scop->mega, av[i + 1]))
			return (0);
		++i;
	}
	return (1);
}

void		get_arg(t_scop *scop, int *ac, char ***av)
{
	scop->color = false;
	if (*ac > 1 && (!ft_strcmp((*av)[1], "-c") ||
	!ft_strcmp((*av)[1], "--color")))
	{
		scop->color = true;
		--(*ac);
		++(*av);
	}
	scop->pos = false;
	if (*ac > 1 && (!ft_strcmp((*av)[1], "-p") ||
	!ft_strcmp((*av)[1], "--position")))
	{
		scop->pos = true;
		--(*ac);
		++(*av);
	}
	if (*ac > 1 && !scop->color && (!ft_strcmp((*av)[1], "-c") ||
	!ft_strcmp((*av)[1], "--color")))
	{
		scop->color = true;
		--(*ac);
		++(*av);
	}
}

int			init_shader_tex_obj(t_scop *scop, int ac, char **av)
{
	if (!(scop->shader = get_shader("resources/shader/basicShader.vs",
"resources/shader/basicShader.gs", "resources/shader/basicShader.fs")))
	{
		quit(&scop->win);
		return (0);
	}
	if (!(scop->shader_normal = get_shader("resources/shader/normalShader.vs",
"resources/shader/normalShader.gs", "resources/shader/normalShader.fs")))
	{
		glDeleteProgram(scop->shader);
		quit(&scop->win);
		return (0);
	}
	init_value(scop);
	if (!get_texture("licorne.bmp", GL_TEXTURE_2D, &scop->mega.tex) ||
	!init_all_obj_file(scop, ac - 1, av))
	{
		free(scop->mega.tex.data);
		delete_mega(&scop->mega);
		glDeleteProgram(scop->shader);
		glDeleteProgram(scop->shader_normal);
		quit(&scop->win);
		return (0);
	}
	return (1);
}

int			init(t_scop *scop, int ac, char **av)
{
	uint	i;

	srand(time(NULL));
	get_arg(scop, &ac, &av);
	if (ac >= 2)
		scop->win = init_window("scop", 800, 600);
	if (ac < 2 || !scop->win.open)
		return (0);
	if (!init_shader_tex_obj(scop, ac, av))
		return (0);
	load_texture(&scop->mega.tex);
	preprocess_mega(&scop->mega, scop->color, scop->pos);
	load_gl_mega(&scop->mega);
	i = 0;
	while (i < scop->mega.nb_material)
	{
		if (scop->mega.materials[i].diffuse_tex.data)
			load_texture(&scop->mega.materials[i].diffuse_tex);
		if (scop->mega.materials[i].specular_tex.data)
			load_texture(&scop->mega.materials[i].specular_tex);
		++i;
	}
	return (1);
}
