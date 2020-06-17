/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mtl_tex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 10:58:57 by niduches          #+#    #+#             */
/*   Updated: 2020/06/17 14:26:11 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int	parse_texture_name(char *line, t_texture *tex)
{
	uint		size;
	char		filename[NAME_MAX + 1];

	if (!tex)
		return (0);
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	size = pass_word(line);
	if (size == 0 || size > NAME_MAX)
		return (0);
	ft_strlcpy(filename, line, size + 1);
	line += size + pass_spaces(line + size);
	if (*line || size < 4 || ft_strcmp(filename + size - 4, ".bmp"))
		return (0);
	if (!get_texture(filename, GL_TEXTURE_2D, tex))
		return (0);
	return (1);
}

int			parse_diffuse_tex(char *line, t_mtl_vector *mtl)
{
	if (!mtl || !mtl->nb_material)
		return (0);
	if (!parse_texture_name(line,
&mtl->materials[mtl->nb_material - 1].diffuse_tex))
		return (0);
	return (1);
}

int			parse_specular_tex(char *line, t_mtl_vector *mtl)
{
	if (!mtl || !mtl->nb_material)
		return (0);
	if (!parse_texture_name(line,
&mtl->materials[mtl->nb_material - 1].specular_tex))
		return (0);
	return (1);
}
