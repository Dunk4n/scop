/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_mtl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 19:01:36 by niduches          #+#    #+#             */
/*   Updated: 2020/06/11 02:03:25 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "scop.h"

//void	remove_comment(char *line, t_mtl_vector *mtl)
//{
//	while (*line)
//	{
//		if (*line == '#')
//		{
//			*line = '\0';
//			return ;
//		}
//		++line;
//	}
//}

int		add_to_mega(t_mtl_vector *mtl, t_mega_obj *mega)
{
	t_material	*new;
	uint		i;
	uint		j;

	if (!mtl->nb_material)
		return (1);
	new = malloc(sizeof(t_material) * (mega->nb_material + mtl->nb_material));
	if (!new)
		return (0);
	i = 0;
	while (i < mega->nb_material)
	{
		new[i] = mega->materials[i];
		++i;
	}
	j = 0;
	while (j < mtl->nb_material)
	{
		new[i + j] = mtl->materials[j];
		++j;
	}
	free(mega->materials);
	mega->materials = new;
	mega->nb_material = mega->nb_material + mtl->nb_material;
	return (1);
}

static int	(* const g_mtl_parse_line[NB_MTL_KEYWORD])
(char *line, t_mtl_vector *mtl) =
{
	parse_newmtl, parse_ambient, parse_diffuse, parse_specular, parse_shininess,
	parse_transparency, parse_inv_transparency, parse_density, parse_illum
};

static const char *keyword[NB_MTL_KEYWORD] =
{
	"newmtl", "Ka", "Kd", "Ks", "Ns", "d", "Tr", "Ni", "illum"
};

static int	get_type(char *line)
{
	unsigned int	i;
	unsigned int	size;

	line += pass_spaces(line);
	if (!*line)
		return (-1);
	size = pass_word(line);
	i = 0;
	while (i < NB_MTL_KEYWORD)
	{
		if (size == ft_strlen(keyword[i]) &&
!ft_strncmp(line, keyword[i], size))
			return (i);
		++i;
	}
	return (-2);
}

int		init_mtl(char *filename, int *fd, t_mtl_vector *mtl)
{
	char	name[256];

	mtl->materials = NULL;
	mtl->nb_material = 0;
	mtl->capacity_material = 0;
	if (!filename)
		return (0);
	ft_strcpy(name, "resources/");
	ft_strcat(name, filename);
	if ((*fd = open(name, O_RDONLY)) < 0)
		return (0);
	return (1);
}

int		load_mtl(char *filename, t_mega_obj *mega)
{
	int				fd;
	int				ret;
	char			*line;
	int				type;
	t_mtl_vector	mtl;


	if (!init_mtl(filename, &fd, &mtl))
		return (0);
	while ((ret = get_next_line(fd, &line)))
	{
		//TODO maybe change capacity	Material Count: 1
		remove_comment(line);
		if ((type = get_type(line)) == -1)
		{
			free(line);
			continue ;
		}
		if (type < 0 || !g_mtl_parse_line[type](line, &mtl))
		{
			ret = -1;
			break ;
		}
		free(line);
		line = NULL;
	}
	free(line);
	close(fd);
	//TODO select used one
	if (ret != -1 && !add_to_mega(&mtl, mega))
		ret = -1;
	free(mtl.materials);
	if (ret == -1)
		return (0);
	return (1);
}
