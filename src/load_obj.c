/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 23:16:38 by niduches          #+#    #+#             */
/*   Updated: 2020/06/17 12:13:07 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "scop.h"

int		add_new_obj(t_mega_obj *mega)
{
	t_obj			*tmp;
	unsigned int	i;

	if (mega->nb_obj == 0)
	{
		if (!(mega->objs = malloc(sizeof(t_obj))))
			return (0);
		++mega->nb_obj;
		init_obj(mega->objs);
		return (1);
	}
	tmp = mega->objs;
	if (!(mega->objs = malloc(sizeof(t_obj) * (mega->nb_obj + 1))))
		return (0);
	i = 0;
	while (i < mega->nb_obj)
	{
		mega->objs[i] = tmp[i];
		++i;
	}
	init_obj(&mega->objs[i]);
	++mega->nb_obj;
	free(tmp);
	return (1);
}

int		init_load(t_mega_obj *mega, const char *name, int *fd, t_load_vertex *array)
{
	if ((*fd = open(name, O_RDONLY)) < 0)
	{
		delete_mega(mega);
		return (0);
	}
	if (!(add_new_obj(mega)))
	{
		delete_mega(mega);
		close(*fd);
		return (0);
	}
	if (!(mega->objs[mega->nb_obj - 1].meshs = malloc(sizeof(t_mesh))))
	{
		delete_mega(mega);
		close(*fd);
		return (0);
	}
	init_mesh(mega->objs[mega->nb_obj - 1].meshs);
	mega->objs[mega->nb_obj - 1].nb_mesh = 1;
	array->position = NULL;
	array->normal = NULL;
	array->texture = NULL;
	array->nb_position = 0;
	array->nb_normal = 0;
	array->nb_texture = 0;
	array->capacity_position = 0;
	array->capacity_normal = 0;
	array->capacity_texture = 0;
	return (1);
}

void	remove_comment(char *line)
{
	while (*line)
	{
		if (*line == '#')
		{
			*line = '\0';
			return ;
		}
		++line;
	}
}

void	delete_array(t_load_vertex *array)
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

static int		(* const g_parse_line[NB_OBJ_KEYWORD])
(char *line, t_load_vertex *array, t_mega_obj *mega) =
{
parse_position, parse_normal, parse_texture, parse_face, parse_group, parse_obj,
parse_s, parse_mtllib, parse_usemtl
};

static const char	*keyword[NB_OBJ_KEYWORD] =
{
"v", "vn", "vt", "f", "g", "o", "s", "mtllib", "usemtl"
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
	while (i < NB_OBJ_KEYWORD)
	{
		if (size == ft_strlen(keyword[i]) &&
!ft_strncmp(line, keyword[i], size))
			return (i);
		++i;
	}
	return (-2);
}

int		load_obj(t_mega_obj *mega, const char *name)
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
		remove_comment(line);
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
	close(fd);
	if (ret == -1)
	{
		get_next_line(fd, NULL);
		delete_array(&array);
		delete_mega(mega);
		return (0);
	}
	format_obj(get_actual_obj(mega), &array);
	delete_array(&array);
	return (1);
}
