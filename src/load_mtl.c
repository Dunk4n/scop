/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_mtl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 19:01:36 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 22:24:16 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "scop.h"

int					add_to_mega(t_mtl_vector *mtl, t_mega_obj *mega)
{
	t_material	*new;
	t_material	*ptr;
	uint		i;
	uint		j;

	if (!mtl->nb_material)
		return (1);
	new = malloc(sizeof(t_material) * (mega->nb_material + mtl->nb_material));
	if (!new)
	{
		free_materials(mtl->materials, mtl->nb_material);
		return (0);
	}
	i = 0;
	ptr = mega->materials;
	while (i < mega->nb_material)
		new[i++] = *(ptr++);
	j = 0;
	ptr = mtl->materials;
	while (j < mtl->nb_material)
		new[i + j++] = *(ptr++);
	free(mega->materials);
	mega->materials = new;
	mega->nb_material = mega->nb_material + mtl->nb_material;
	return (1);
}

static int			(*const g_mtl_parse_line[NB_MTL_KEYWORD])
(char *line, t_mtl_vector *mtl) =
{
	parse_newmtl, parse_ambient, parse_diffuse, parse_specular, parse_shininess,
	parse_transparency, parse_inv_transparency, parse_density, parse_illum,
	parse_diffuse_tex, parse_specular_tex,
};

static const char	*g_keyword[NB_MTL_KEYWORD] =
{
	"newmtl", "Ka", "Kd", "Ks", "Ns", "d", "Tr", "Ni", "illum", "map_Kd",
	"map_Ks",
};

static int			get_type(char *line)
{
	unsigned int	i;
	unsigned int	size;

	if (!line)
		return (-2);
	line += pass_spaces(line);
	if (!*line)
		return (-1);
	size = pass_word(line);
	i = 0;
	while (i < NB_MTL_KEYWORD)
	{
		if (size == ft_strlen(g_keyword[i]) &&
!ft_strncmp(line, g_keyword[i], size))
			return (i);
		++i;
	}
	return (-2);
}

int					init_mtl(char *filename, int *fd, t_mtl_vector *mtl)
{
	mtl->materials = NULL;
	mtl->nb_material = 0;
	mtl->capacity_material = 0;
	if (!filename)
		return (0);
	if ((*fd = open(filename, O_RDONLY)) < 0)
		return (0);
	return (1);
}

static int			end_load_mtl(t_mega_obj *mega, t_mtl_vector *mtl,
int fd, int ret)
{
	close(fd);
	if (ret > -1 && !add_to_mega(mtl, mega))
		ret = -1;
	free(mtl->materials);
	if (ret < 0)
	{
		free_materials(mtl->materials, mtl->nb_material);
		get_next_line(fd, NULL);
		return (0);
	}
	return (1);
}

int					load_mtl(char *filename, t_mega_obj *mega)
{
	int				fd;
	char			*line;
	int				type;
	t_mtl_vector	mtl;

	if (!init_mtl(filename, &fd, &mtl))
		return (0);
	while ((type = get_next_line(fd, &line)))
	{
		remove_mtl_comment(&line, &mtl);
		if ((type = get_type(line)) == -1)
		{
			free(line);
			continue ;
		}
		if (type < 0 || !g_mtl_parse_line[type](line, &mtl))
		{
			type = -1;
			break ;
		}
		free(line);
		line = NULL;
	}
	free(line);
	return (end_load_mtl(mega, &mtl, fd, type));
}
