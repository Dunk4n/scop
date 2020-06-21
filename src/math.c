/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 20:37:48 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 16:57:56 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vec3f	sub_vec3f(t_vec3f a, t_vec3f b)
{
	return ((t_vec3f){a.x - b.x, a.y - b.y, a.z - b.z});
}

void	rotation_result(t_mat4 *res, t_mat4 new, t_mat4 mat, int nb)
{
	if (nb == 3)
	{
		res->val[3][0] = mat.val[3][0];
		res->val[3][1] = mat.val[3][1];
		res->val[3][2] = mat.val[3][2];
		res->val[3][3] = mat.val[3][3];
		return ;
	}
	res->val[nb][0] = mat.val[0][0] * new.val[nb][0] + mat.val[1][0] *
	new.val[nb][1] + mat.val[2][0] * new.val[nb][2];
	res->val[nb][1] = mat.val[0][1] * new.val[nb][0] + mat.val[1][1] *
	new.val[nb][1] + mat.val[2][1] * new.val[nb][2];
	res->val[nb][2] = mat.val[0][2] * new.val[nb][0] + mat.val[1][2] *
	new.val[nb][1] + mat.val[2][2] * new.val[nb][2];
	res->val[nb][3] = mat.val[0][3] * new.val[nb][0] + mat.val[1][3] *
	new.val[nb][1] + mat.val[2][3] * new.val[nb][2];
}

t_mat4	rotation_matrix(t_mat4 mat, float angl, t_vec3f vec)
{
	t_vec2f	cosinus;
	t_vec3f	tmp;
	t_mat4	new;
	t_mat4	res;

	cosinus.x = cos(angl);
	cosinus.y = sin(angl);
	vec = normalize_vector(vec);
	tmp = mult_vector(vec, 1.0 - cosinus.x);
	ft_bzero((void*)&new, sizeof(t_mat4));
	new.val[0][0] = cosinus.x + tmp.x * vec.x;
	new.val[0][1] = tmp.x * vec.y + cosinus.y * vec.z;
	new.val[0][2] = tmp.x * vec.z - cosinus.y * vec.y;
	new.val[1][0] = tmp.y * vec.x - cosinus.y * vec.z;
	new.val[1][1] = cosinus.x + tmp.y * vec.y;
	new.val[1][2] = tmp.y * vec.z + cosinus.y * vec.x;
	new.val[2][0] = tmp.z * vec.x + cosinus.y * vec.y;
	new.val[2][1] = tmp.z * vec.y - cosinus.y * vec.x;
	new.val[2][2] = cosinus.x + tmp.z * vec.z;
	ft_bzero((void*)&res, sizeof(t_mat4));
	rotation_result(&res, new, mat, 0);
	rotation_result(&res, new, mat, 1);
	rotation_result(&res, new, mat, 2);
	rotation_result(&res, new, mat, 3);
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
