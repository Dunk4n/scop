/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 20:37:48 by niduches          #+#    #+#             */
/*   Updated: 2020/06/17 18:21:24 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vec3f	sub_vec3f(t_vec3f a, t_vec3f b)
{
	return ((t_vec3f){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_mat4	identity_matrix(void)
{
	t_mat4	mat;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			mat.val[i][j] = (i == j) ? 1 : 0;
	}
	return (mat);
}

t_mat4	mult_matrix(t_mat4 mat1, t_mat4 mat2)
{
	t_mat4	new;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			new.val[i][j] = 0;
			for (int k = 0; k < 4; ++k)
				new.val[i][j] += mat1.val[i][k] * mat2.val[k][j];
		}
	}
	return (new);
}

t_mat4	translation_matrix(t_mat4 mat, t_vec3f vec)
{
	t_mat4	new;

	new = identity_matrix();
	new.val[0][3] = vec.x;
	new.val[1][3] = vec.y;
	new.val[2][3] = vec.z;
	return (mult_matrix(mat, new));
}

t_mat4	rotation_matrix(t_mat4 mat, float angl, t_vec3f vec)
{
	t_mat4	new;
	float	tmp;

	new = identity_matrix();
	tmp = angl * vec.x;
	new.val[1][1] = cos(tmp);
	new.val[1][2] = -sin(tmp);
	new.val[2][1] = sin(tmp);
	new.val[2][2] = cos(tmp);
	mat = mult_matrix(mat, new);
	new = identity_matrix();
	tmp = angl * vec.y;
	new.val[0][0] = cos(tmp);
	new.val[0][2] = sin(tmp);
	new.val[2][0] = -sin(tmp);
	new.val[2][2] = cos(tmp);
	mat = mult_matrix(mat, new);
	new = identity_matrix();
	tmp = angl * vec.z;
	new.val[0][0] = cos(tmp);
	new.val[0][1] = sin(tmp);
	new.val[1][0] = -sin(tmp);
	new.val[1][1] = cos(tmp);
	return (mult_matrix(mat, new));
}

t_mat4	scale_matrix(t_mat4 mat, t_vec3f vec)
{
	t_mat4	new;

	new = identity_matrix();
	new.val[0][0] = vec.x;
	new.val[1][1] = vec.y;
	new.val[2][2] = vec.z;
	return (mult_matrix(mat, new));
}

t_mat4	perspective_matrix(float fov, float ar, float near, float far)
{
	t_mat4	new;
	float	tan_half_fov;

	ft_bzero((void*)&new, sizeof(t_mat4));
	if (ar == 0 || far == near)
		return (new);
	tan_half_fov = tan((fov * M_PI / 180.0) / 2.0);
	new.val[0][0] = 1.0 / (ar * tan_half_fov);
	new.val[1][1] = 1.0 / tan_half_fov;
	new.val[2][2] = -(far + near) / (far - near);
	new.val[2][3] = -1.0;
	new.val[3][2] = -(2.0 * far * near) / (far - near);
	return (new);
}
