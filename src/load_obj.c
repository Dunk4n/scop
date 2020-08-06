/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 23:16:38 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 22:23:44 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void				delete_array(t_load_vertex *array)
{
	free(array->position);
	free(array->normal);
	free(array->texture);
	array->position = NULL;
	array->normal = NULL;
	array->texture = NULL;
	array->nb_position = 0;
	array->nb_normal = 0;
	array->nb_texture = 0;
	array->capacity_position = 0;
	array->capacity_normal = 0;
	array->capacity_texture = 0;
}

static int			(*const g_parse_line[NB_OBJ_KEYWORD])
(char *line, t_load_vertex *array, t_mega_obj *mega) =
{
	parse_position, parse_normal, parse_texture, parse_face, parse_group,
	parse_obj, parse_s, parse_mtllib, parse_usemtl
};

static const char	*g_keyword[NB_OBJ_KEYWORD] =
{
	"v", "vn", "vt", "f", "g", "o", "s", "mtllib", "usemtl"
};

static int			get_type(char *line)
{
	unsigned int	i;
	unsigned int	size;

	remove_comment(line);
	line += pass_spaces(line);
	if (!*line)
		return (-1);
	size = pass_word(line);
	i = 0;
	while (i < NB_OBJ_KEYWORD)
	{
		if (size == ft_strlen(g_keyword[i]) &&
!ft_strncmp(line, g_keyword[i], size))
			return (i);
		++i;
	}
	return (-2);
}

int					load_obj_end(t_mega_obj *mega, t_load_vertex *array,
int ret, int fd)
{
	close(fd);
	if (ret == -1)
	{
		get_next_line(fd, NULL);
		delete_array(array);
		delete_mega(mega);
		return (0);
	}
	format_obj(get_actual_obj(mega), array);
	delete_array(array);
	return (1);
}

int					load_obj(t_mega_obj *mega, const char *name)
{
	int				fd;
	int				ret;
	char			*line;
	int				type;
	t_load_vertex	array;

	if (!init_load(mega, name, &fd, &array))
		return (0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if ((type = get_type(line)) == -1)
		{
			free(line);
			continue ;
		}
		if (type < 0 || !g_parse_line[type](line, &array, mega))
		{
			ret = -1;
			break ;
		}
		free(line);
		line = NULL;
	}
	free(line);
	return (load_obj_end(mega, &array, ret, fd));
}
