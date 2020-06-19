/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 20:37:48 by niduches          #+#    #+#             */
/*   Updated: 2020/06/19 15:53:57 by niduches         ###   ########.fr       */
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
	new.val[3][0] = vec.x;
	new.val[3][1] = vec.y;
	new.val[3][2] = vec.z;
	return (mult_matrix(mat, new));
}

t_mat4	rotation_matrix(t_mat4 mat, float angl, t_vec3f vec)
{
	float	c;
	float	s;
	t_vec3f	tmp;
	t_mat4	new;

	c = cos(angl);
	s = sin(angl);
	vec = normalize_vector(vec);
	tmp = mult_vector(vec, 1.0 - c);
	ft_bzero((void*)&new, sizeof(t_mat4));
	new.val[0][0] = c + tmp.x * vec.x;
	new.val[0][1] = tmp.x * vec.y + s * vec.z;
	new.val[0][2] = tmp.x * vec.z - s * vec.y;

	new.val[1][0] = tmp.y * vec.x - s * vec.z;
	new.val[1][1] = c + tmp.y * vec.y;
	new.val[1][2] = tmp.y * vec.z + s * vec.x;

	new.val[2][0] = tmp.z * vec.x + s * vec.y;
	new.val[2][1] = tmp.z * vec.y - s * vec.x;
	new.val[2][2] = c + tmp.z * vec.z;

	t_mat4	res;
	ft_bzero((void*)&res, sizeof(t_mat4));
	res.val[0][0] = mat.val[0][0] * new.val[0][0] + mat.val[1][0] * new.val[0][1] + mat.val[2][0] * new.val[0][2];
	res.val[0][1] = mat.val[0][1] * new.val[0][0] + mat.val[1][1] * new.val[0][1] + mat.val[2][1] * new.val[0][2];
	res.val[0][2] = mat.val[0][2] * new.val[0][0] + mat.val[1][2] * new.val[0][1] + mat.val[2][2] * new.val[0][2];
	res.val[0][3] = mat.val[0][3] * new.val[0][0] + mat.val[1][3] * new.val[0][1] + mat.val[2][3] * new.val[0][2];

	res.val[1][0] = mat.val[0][0] * new.val[1][0] + mat.val[1][0] * new.val[1][1] + mat.val[2][0] * new.val[1][2];
	res.val[1][1] = mat.val[0][1] * new.val[1][0] + mat.val[1][1] * new.val[1][1] + mat.val[2][1] * new.val[1][2];
	res.val[1][2] = mat.val[0][2] * new.val[1][0] + mat.val[1][2] * new.val[1][1] + mat.val[2][2] * new.val[1][2];
	res.val[1][3] = mat.val[0][3] * new.val[1][0] + mat.val[1][3] * new.val[1][1] + mat.val[2][3] * new.val[1][2];

	res.val[2][0] = mat.val[0][0] * new.val[2][0] + mat.val[1][0] * new.val[2][1] + mat.val[2][0] * new.val[2][2];
	res.val[2][1] = mat.val[0][1] * new.val[2][0] + mat.val[1][1] * new.val[2][1] + mat.val[2][1] * new.val[2][2];
	res.val[2][2] = mat.val[0][2] * new.val[2][0] + mat.val[1][2] * new.val[2][1] + mat.val[2][2] * new.val[2][2];
	res.val[2][3] = mat.val[0][3] * new.val[2][0] + mat.val[1][3] * new.val[2][1] + mat.val[2][3] * new.val[2][2];

	res.val[3][0] = mat.val[3][0];
	res.val[3][1] = mat.val[3][1];
	res.val[3][2] = mat.val[3][2];
	res.val[3][3] = mat.val[3][3];
	return (res);
}

t_mat4	scale_matrix(t_mat4 mat, t_vec3f vec)
{
	t_mat4	new;

	ft_bzero((void*)&new, sizeof(t_mat4));
	new.val[0][0] = mat.val[0][0] * vec.x;
	new.val[0][1] = mat.val[0][1] * vec.x;
	new.val[0][2] = mat.val[0][2] * vec.x;
	new.val[0][3] = mat.val[0][3] * vec.x;

	new.val[1][0] = mat.val[1][0] * vec.y;
	new.val[1][1] = mat.val[1][1] * vec.y;
	new.val[1][2] = mat.val[1][2] * vec.y;
	new.val[1][3] = mat.val[1][3] * vec.y;

	new.val[2][0] = mat.val[2][0] * vec.z;
	new.val[2][1] = mat.val[2][1] * vec.z;
	new.val[2][2] = mat.val[2][2] * vec.z;
	new.val[2][3] = mat.val[2][3] * vec.z;

	new.val[3][0] = mat.val[3][0];
	new.val[3][1] = mat.val[3][1];
	new.val[3][2] = mat.val[3][2];
	new.val[3][3] = mat.val[3][3];
	return (new);
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
