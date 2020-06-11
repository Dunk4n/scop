/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mtl_one_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 20:26:53 by niduches          #+#    #+#             */
/*   Updated: 2020/06/11 18:38:45 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		parse_shininess(char *line, t_mtl_vector *mtl)
{
	if (mtl->nb_material == 0)
		return (0);
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	line += get_float(line, &mtl->materials[mtl->nb_material - 1].shininess);
	if (mtl->materials[mtl->nb_material - 1].shininess < 0 ||
	mtl->materials[mtl->nb_material - 1].shininess > 1000)
		return (0);
	if (mtl->materials[mtl->nb_material - 1].shininess < 1)
		mtl->materials[mtl->nb_material - 1].shininess = 1;
	line += pass_spaces(line);
	if (*line)
		return (0);
	return (1);
}

int		parse_transparency(char *line, t_mtl_vector *mtl)
{
	if (mtl->nb_material == 0)
		return (0);
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	line += get_float(line, &mtl->materials[mtl->nb_material - 1].transparency);
	if (mtl->materials[mtl->nb_material - 1].transparency < 0 ||
	mtl->materials[mtl->nb_material - 1].transparency > 1)
		return (0);
	line += pass_spaces(line);
	if (*line)
		return (0);
	return (1);
}

int		parse_inv_transparency(char *line, t_mtl_vector *mtl)
{
	if (mtl->nb_material == 0)
		return (0);
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	line += get_float(line, &mtl->materials[mtl->nb_material - 1].transparency);
	mtl->materials[mtl->nb_material - 1].transparency =
	1 - mtl->materials[mtl->nb_material - 1].transparency;
	if (mtl->materials[mtl->nb_material - 1].transparency < 0 ||
	mtl->materials[mtl->nb_material - 1].transparency > 1)
		return (0);
	line += pass_spaces(line);
	if (*line)
		return (0);
	return (1);
}

int		parse_density(char *line, t_mtl_vector *mtl)
{
	if (mtl->nb_material == 0)
		return (0);
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	line += get_float(line, &mtl->materials[mtl->nb_material - 1].dencity);
	if (mtl->materials[mtl->nb_material - 1].dencity < 0.001 ||
	mtl->materials[mtl->nb_material - 1].dencity > 10)
		return (0);
	line += pass_spaces(line);
	if (*line)
		return (0);
	return (1);
}

int		parse_illum(char *line, t_mtl_vector *mtl)
{
	uint	tmp;

	if (mtl->nb_material == 0)
		return (0);
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	line += get_uint(line, &tmp);
	mtl->materials[mtl->nb_material - 1].illum = tmp;
	if (mtl->materials[mtl->nb_material - 1].illum != 2)
		return (0);
	line += pass_spaces(line);
	if (*line)
		return (0);
	return (1);
}
