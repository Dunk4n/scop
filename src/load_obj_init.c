/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 15:39:23 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 15:41:34 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "scop.h"

static int	add_new_obj(t_mega_obj *mega)
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

int			init_load(t_mega_obj *mega, const char *name, int *fd,
t_load_vertex *array)
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
	ft_bzero((char*)array, sizeof(t_load_vertex));
	return (1);
}

void		remove_comment(char *line)
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
