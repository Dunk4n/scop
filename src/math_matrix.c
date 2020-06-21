/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 16:57:04 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 17:41:23 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_mat4	identity_matrix(void)
{
	t_mat4	mat;
	uint	i;
	uint	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mat.val[i][j] = (i == j) ? 1 : 0;
			++j;
		}
		++i;
	}
	return (mat);
}

t_mat4	mult_matrix(t_mat4 mat1, t_mat4 mat2)
{
	t_mat4	new;
	uint	i;
	uint	j;
	uint	k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			new.val[i][j] = 0;
			k = 0;
			while (k < 4)
			{
				new.val[i][j] += mat1.val[i][k] * mat2.val[k][j];
				++k;
			}
			++j;
		}
	}
	return (new);
}

t_mat4	translation_matrix(t_mat4 mat, t_vec3f vec)
{
	t_mat4	new;

	new = identity_matrix();
	new.val[3][0] = vec.x;
	new.val[3][1] = vec.y;
	new.val[3][2] = vec.z;
	return (mult_matrix(mat, new));
}
