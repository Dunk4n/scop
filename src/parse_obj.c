/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 19:03:27 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 17:45:40 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_mesh		*get_actual_mesh(t_mega_obj *mega)
{
	return (&mega->objs[mega->nb_obj - 1].meshs[mega->objs[mega->nb_obj -
1].nb_mesh - 1]);
}

t_obj		*get_actual_obj(t_mega_obj *mega)
{
	return (&mega->objs[mega->nb_obj - 1]);
}

static int	add_new_obj(t_mega_obj *mega)
{
	t_obj			*tmp;
	unsigned int	i;

	tmp = mega->objs;
	if (!(mega->objs = malloc(sizeof(t_obj) * (mega->nb_obj + 1))))
		return (0);
	i = 0;
	while (i < mega->nb_obj)
	{
		mega->objs[i] = tmp[i];
		++i;
	}
	++mega->nb_obj;
	free(tmp);
	init_obj(&mega->objs[i]);
	if (!(mega->objs[i].meshs = malloc(sizeof(t_mesh))))
		return (0);
	mega->objs[i].nb_mesh = 1;
	init_mesh(mega->objs[i].meshs);
	return (1);
}

int			parse_obj(char *line, t_load_vertex *array, t_mega_obj *mega)
{
	char	name[64];
	int		j;

	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	j = pass_word(line);
	ft_strncpy(name, line, (j > 63) ? 63 : j);
	line += pass_spaces(line + j) + j;
	if (*line)
		return (0);
	if ((get_actual_obj(mega)->nb_mesh > 1 ||
get_actual_mesh(mega)->nb_index > 0))
	{
		format_obj(get_actual_obj(mega), array);
		if (!add_new_obj(mega))
			return (0);
	}
	ft_strcpy(get_actual_obj(mega)->name, name);
	return (1);
}
