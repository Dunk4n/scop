/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mtl_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 20:53:16 by niduches          #+#    #+#             */
/*   Updated: 2020/06/20 21:11:28 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int	realloc_mtl(t_mtl_vector *mtl)
{
	t_material	*new;
	uint		i;

	if (mtl->capacity_material >= 10000)
		return (0);
	mtl->capacity_material = !mtl->capacity_material ?
	1 : mtl->capacity_material * 2;
	new = malloc(sizeof(t_material) * (mtl->capacity_material));
	if (!new)
	{
		free(mtl->materials);
		mtl->materials = NULL;
		return (0);
	}
	i = 0;
	while (i < mtl->nb_material)
	{
		new[i] = mtl->materials[i];
		++i;
	}
	free(mtl->materials);
	mtl->materials = new;
	return (1);
}

static void	init_new_material(t_material *mat)
{
	mat->ambient = (t_vec3f){0, 0, 0};
	mat->diffuse = (t_vec3f){0, 0, 0};
	mat->specular = (t_vec3f){0, 0, 0};
	mat->shininess = 0;
	mat->transparency = 1;
	mat->dencity = 1;
	mat->illum = 2;
	mat->diffuse_tex.data = NULL;
	mat->specular_tex.data = NULL;
}

int			parse_newmtl(char *line, t_mtl_vector *mtl)
{
	uint		size;
	t_material	*mat;

	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	size = pass_word(line);
	if (size == 0 || size > 63)
		return (0);
	if (mtl->nb_material >= mtl->capacity_material && !realloc_mtl(mtl))
		return (0);
	mat = &mtl->materials[mtl->nb_material];
	ft_strlcpy(mat->name, line, size + 1);
	line += size + pass_spaces(line + size);
	if (*line)
		return (0);
	init_new_material(mat);
	++mtl->nb_material;
	return (1);
}

int			parse_ambient(char *line, t_mtl_vector *mtl)
{
	t_vec3f	new;

	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	line += get_float(line, &new.x);
	line += pass_spaces(line);
	line += get_float(line, &new.y);
	line += pass_spaces(line);
	if (!*line)
		return (0);
	line += get_float(line, &new.z);
	line += pass_spaces(line);
	if (*line || new.x < 0 || new.x > 1 || new.y < 0 || new.y > 1 ||
new.z < 0 || new.z > 1)
		return (0);
	mtl->materials[mtl->nb_material - 1].ambient = new;
	return (1);
}

int			parse_diffuse(char *line, t_mtl_vector *mtl)
{
	t_vec3f	new;

	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	line += get_float(line, &new.x);
	line += pass_spaces(line);
	line += get_float(line, &new.y);
	line += pass_spaces(line);
	if (!*line)
		return (0);
	line += get_float(line, &new.z);
	line += pass_spaces(line);
	if (*line || new.x < 0 || new.x > 1 || new.y < 0 || new.y > 1 ||
new.z < 0 || new.z > 1)
		return (0);
	mtl->materials[mtl->nb_material - 1].diffuse = new;
	return (1);
}

int			parse_specular(char *line, t_mtl_vector *mtl)
{
	t_vec3f	new;

	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	line += get_float(line, &new.x);
	line += pass_spaces(line);
	line += get_float(line, &new.y);
	line += pass_spaces(line);
	if (!*line)
		return (0);
	line += get_float(line, &new.z);
	line += pass_spaces(line);
	if (*line || new.x < 0 || new.x > 1 || new.y < 0 || new.y > 1 ||
new.z < 0 || new.z > 1)
		return (0);
	mtl->materials[mtl->nb_material - 1].specular = new;
	return (1);
}
