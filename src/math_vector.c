/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 15:17:56 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 17:24:05 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vec3f	mult_matrix_vector(t_vec3f vec, t_mat4 mat)
{
	t_vec3f	new;

	new.x = mat.val[0][0] * vec.x + mat.val[0][1] * vec.y + mat.val[0][2] *
	vec.z + mat.val[0][3];
	new.y = mat.val[1][0] * vec.x + mat.val[1][1] * vec.y + mat.val[1][2] *
	vec.z + mat.val[1][3];
	new.z = mat.val[2][0] * vec.x + mat.val[2][1] * vec.y + mat.val[2][2] *
	vec.z + mat.val[2][3];
	return (new);
}

t_vec3f	normalize_vector(t_vec3f vec)
{
	float	length;

	length = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	if (length == 0)
		return (vec);
	if (length < 0)
		length = -length;
	vec.x /= length;
	vec.y /= length;
	vec.z /= length;
	return (vec);
}
