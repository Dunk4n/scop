/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vertex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 13:12:27 by niduches          #+#    #+#             */
/*   Updated: 2020/04/24 19:01:12 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static int	add_new_vertex(t_vec3f new, t_vec3f **array,
unsigned int *nb, unsigned int *capacity)
{
	t_vec3f			*tmp;
	unsigned int	i;

	if (*capacity > *nb)
	{
		(*array)[*nb] = new;
		++(*nb);
		return (1);
	}
	tmp = *array;
	*capacity = (!*capacity) ? 1 : *capacity * 2;
	if (!(*array = malloc(sizeof(t_vec3f) * *capacity)))
		return (0);
	i = 0;
	while (i < *nb)
	{
		(*array)[i] = tmp[i];
		++i;
	}
	(*array)[i] = new;
	++(*nb);
	free(tmp);
	return (1);
}

static int	add_new_texture(t_vec2f new, t_vec2f **array,
unsigned int *nb, unsigned int *capacity)
{
	t_vec2f			*tmp;
	unsigned int	i;

	if (*capacity > *nb)
	{
		(*array)[*nb] = new;
		++(*nb);
		return (1);
	}
	tmp = *array;
	*capacity = (!*capacity) ? 1 : *capacity * 2;
	if (!(*array = malloc(sizeof(t_vec2f) * *capacity)))
		return (0);
	i = 0;
	while (i < *nb)
	{
		(*array)[i] = tmp[i];
		++i;
	}
	(*array)[i] = new;
	++(*nb);
	free(tmp);
	return (1);
}

int			parse_position(char *line, t_load_vertex *array, t_mega_obj *mega)
{
	t_vec3f	new;

	(void)mega;
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	line += get_float(line, &new.x);
	line += pass_spaces(line);
	line += get_float(line, &new.y);
	line += pass_spaces(line);
	line += get_float(line, &new.z);
	line += pass_spaces(line);
	if (*line)
		return (0);
	if (!add_new_vertex(new, &array->position,
&array->nb_position, &array->capacity_position))
		return (0);
	return (1);
}

int			parse_normal(char *line, t_load_vertex *array, t_mega_obj *mega)
{
	t_vec3f	new;

	(void)mega;
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	line += get_float(line, &new.x);
	line += pass_spaces(line);
	line += get_float(line, &new.y);
	line += pass_spaces(line);
	line += get_float(line, &new.z);
	line += pass_spaces(line);
	if (*line)
		return (0);
	if (!add_new_vertex(new, &array->normal,
&array->nb_normal, &array->capacity_normal))
		return (0);
	return (1);
}

int			parse_texture(char *line, t_load_vertex *array, t_mega_obj *mega)
{
	t_vec2f	new;

	(void)mega;
	line += pass_spaces(line);
	line += pass_word(line);
	line += pass_spaces(line);
	line += get_float(line, &new.x);
	line += pass_spaces(line);
	line += get_float(line, &new.y);
	line += pass_spaces(line);
	if (*line || new.x < 0 || new.x > 1 || new.y < 0 || new.y > 1)
		return (0);
	if (!add_new_texture(new, &array->texture,
&array->nb_texture, &array->capacity_texture))
		return (0);
	return (1);
}
