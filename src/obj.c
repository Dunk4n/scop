/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 01:01:06 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 15:24:33 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	move_mega(t_mega_obj *mega, t_vec3f move)
{
	uint	i;

	i = 0;
	while (i < mega->nb_obj)
	{
		mega->objs[i].position.x += move.x;
		mega->objs[i].position.y += move.y;
		mega->objs[i].position.z += move.z;
		++i;
	}
}

void	move_origine_mega(t_mega_obj *mega, t_vec3f move)
{
	uint	i;

	i = 0;
	while (i < mega->nb_obj)
	{
		mega->objs[i].origin.x += move.x;
		mega->objs[i].origin.y += move.y;
		mega->objs[i].origin.z += move.z;
		++i;
	}
}

void	move_and_origine_mega(t_mega_obj *mega, t_vec3f move)
{
	uint	i;

	i = 0;
	while (i < mega->nb_obj)
	{
		mega->objs[i].position.x += move.x;
		mega->objs[i].position.y += move.y;
		mega->objs[i].position.z += move.z;
		mega->objs[i].origin.x += move.x;
		mega->objs[i].origin.y += move.y;
		mega->objs[i].origin.z += move.z;
		++i;
	}
}

void	rotate_mega(t_mega_obj *mega, t_vec3f rotate)
{
	uint	i;

	i = 0;
	while (i < mega->nb_obj)
	{
		mega->objs[i].rotation.x += rotate.x;
		while (mega->objs[i].rotation.x > 360)
			mega->objs[i].rotation.x -= 360;
		while (mega->objs[i].rotation.x < -360)
			mega->objs[i].rotation.x += 360;
		mega->objs[i].rotation.y += rotate.y;
		while (mega->objs[i].rotation.y > 360)
			mega->objs[i].rotation.y -= 360;
		while (mega->objs[i].rotation.y < -360)
			mega->objs[i].rotation.y += 360;
		mega->objs[i].rotation.z += rotate.z;
		while (mega->objs[i].rotation.z > 360)
			mega->objs[i].rotation.z -= 360;
		while (mega->objs[i].rotation.z < -360)
			mega->objs[i].rotation.z += 360;
		++i;
	}
}

void	scale_mega(t_mega_obj *mega, t_vec3f scale)
{
	uint	i;

	i = 0;
	while (i < mega->nb_obj)
	{
		mega->objs[i].scale.x = (mega->objs[i].scale.x + scale.x < 0) ?
		0 : (scale.x + mega->objs[i].scale.x);
		mega->objs[i].scale.y = (mega->objs[i].scale.y + scale.y < 0) ?
		0 : (scale.y + mega->objs[i].scale.y);
		mega->objs[i].scale.z = (mega->objs[i].scale.z + scale.z < 0) ?
		0 : (scale.z + mega->objs[i].scale.z);
		++i;
	}
}
