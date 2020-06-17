/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 14:05:26 by niduches          #+#    #+#             */
/*   Updated: 2020/06/17 14:34:03 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	move_camera(t_camera *cam, double dt, t_vec3f pos)
{
	cam->position = add_vector(cam->position,
	mult_vector(cam->right, pos.x * cam->movement_speed * dt));
	cam->position = add_vector(cam->position,
	mult_vector(cam->up, pos.y * cam->movement_speed * dt));
	cam->position = add_vector(cam->position,
	mult_vector(cam->front, pos.z * cam->movement_speed * dt));
}

void	rotate_camera(t_camera *cam, double dt, t_vec2f rot)
{
	cam->pitch += rot.x * cam->sensitivity * dt;
	cam->yaw += rot.y * cam->sensitivity * dt;
	if (cam->pitch > 90)
		cam->pitch = 90;
	if (cam->pitch < -90)
		cam->pitch = -90;
	while (cam->yaw > 360)
		cam->yaw -= 360;
	while (cam->yaw < -360)
		cam->yaw += 360;
}

void	update_camera_vector(t_camera *cam)
{
	cam->front.x = cos(cam->yaw * M_PI / 180.0) * cos(cam->pitch * M_PI / 180.0);
	cam->front.y = sin(cam->pitch * M_PI / 180.0);
	cam->front.z = sin(cam->yaw * M_PI / 180.0) * cos(cam->pitch * M_PI / 180.0);

	cam->front = normalize_vector(cam->front);
	cam->right = normalize_vector(cross_vector(cam->front, cam->world_up));
	cam->up = normalize_vector(cross_vector(cam->right, cam->front));
}

t_mat4		get_view_matrix(t_camera *cam)
{
	t_vec3f	f;
	t_vec3f	s;
	t_vec3f	u;
	t_vec3f	eye;

	update_camera_vector(cam);
	eye = add_vector(cam->position, cam->front);
	f = normalize_vector(sub_vector(cam->position, eye));
	s = normalize_vector(cross_vector(f, cam->up));
	u = cross_vector(s, f);
	cam->view_matrix = identity_matrix();
	cam->view_matrix.val[0][0] = s.x;
	cam->view_matrix.val[1][0] = s.y;
	cam->view_matrix.val[2][0] = s.z;
	cam->view_matrix.val[0][1] = u.x;
	cam->view_matrix.val[1][1] = u.y;
	cam->view_matrix.val[2][1] = u.z;
	cam->view_matrix.val[0][2] = f.x;
	cam->view_matrix.val[1][2] = f.y;
	cam->view_matrix.val[2][2] = f.z;
	cam->view_matrix.val[3][0] = -dot_vector(s, eye);
	cam->view_matrix.val[3][1] = -dot_vector(u, eye);
	cam->view_matrix.val[3][2] = -dot_vector(f, eye);
	return (cam->view_matrix);
}

t_camera		init_cam()
{
	t_camera	cam;

	cam.view_matrix = identity_matrix();
	cam.movement_speed = 3.0;
	cam.sensitivity = 5.0;
	cam.world_up = (t_vec3f){0, 1, 0};
	cam.position = (t_vec3f){0, 0, -1.3};
	cam.right = (t_vec3f){0, 0, 0};
	cam.up = cam.world_up;

	cam.pitch = 0;
	cam.yaw = 90;
	cam.roll = 0;
	update_camera_vector(&cam);
	return (cam);
}
