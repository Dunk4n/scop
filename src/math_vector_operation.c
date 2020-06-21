/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vector_operation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 17:23:12 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 17:23:51 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vec3f	cross_vector(t_vec3f a, t_vec3f b)
{
	t_vec3f	new;

	new.x = a.y * b.z - a.z * b.y;
	new.y = a.z * b.x - a.x * b.z;
	new.z = a.x * b.y - a.y * b.x;
	return (new);
}

t_vec3f	add_vector(t_vec3f a, t_vec3f b)
{
	return ((t_vec3f){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3f	sub_vector(t_vec3f a, t_vec3f b)
{
	return ((t_vec3f){a.x - b.x, a.y - b.y, a.z - b.z});
}

float	dot_vector(t_vec3f a, t_vec3f b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3f	mult_vector(t_vec3f vec, float nb)
{
	return ((t_vec3f){vec.x * nb, vec.y * nb, vec.z * nb});
}
