/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_group.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 18:57:34 by niduches          #+#    #+#             */
/*   Updated: 2020/04/24 19:42:01 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int	add_new_mesh(t_obj *obj)
{
	t_mesh			*tmp;
	unsigned int	i;

	tmp = obj->meshs;
	if (!(obj->meshs = malloc(sizeof(t_mesh) * (obj->nb_mesh + 1))))
		return (0);
	i = 0;
	while (i < obj->nb_mesh)
	{
		obj->meshs[i] = tmp[i];
		++i;
	}
	++obj->nb_mesh;
	free(tmp);
	return (1);
}

int			parse_group(char *line, t_load_vertex *array, t_mega_obj *mega)
{
	char	name[64];
	int		i;
	int		j;

	(void)array;
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	j = pass_word(line);
	i = 0;
	while (i < j && i < 63)
	{
		name[i] = line[i];
		++i;
	}
	name[i] = '\0';
	line += pass_spaces(line + j) + j;
	if (*line)
		return (0);
	if (get_actual_mesh(mega)->nb_index > 0 &&
!add_new_mesh(get_actual_obj(mega)))
		return (0);
	init_mesh(get_actual_mesh(mega));
	ft_strcpy(get_actual_mesh(mega)->name, name);
	return (1);
}
