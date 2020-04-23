/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 14:41:51 by niduches          #+#    #+#             */
/*   Updated: 2020/04/22 19:28:27 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <GL/glew.h>
# include <SDL2/SDL.h>

typedef struct	s_vec2f
{
	float	x;
	float	y;
}				t_vec2f;

typedef struct	s_vec3f
{
	float	x;
	float	y;
	float	z;
}				t_vec3f;

typedef struct	s_vertex
{
	t_vec3f	position;
	t_vec3f	color;
	t_vec2f	texcoord;
}				t_vertex;

typedef struct	s_mat4
{
	float	val[4][4];
}				t_mat4;

typedef struct	s_mesh
{
	t_vec3f			position;
	t_vec3f			origin;
	t_vec3f			rotation;
	t_vec3f			scale;
	t_mat4			model_matrix;
	GLuint			array_obj;
	GLuint			array_buffer;
	GLuint			array_buffer_index;
	t_vertex		*vertex;
	unsigned int	*index;
	unsigned int	nb_vertex;
	unsigned int	nb_index;
}				t_mesh;

typedef struct	s_camera
{
	t_mat4	view_matrix;
	t_vec3f	world_up;
	t_vec3f	position;
	t_vec3f	front;
	t_vec3f	right;
	t_vec3f	up;
	GLfloat	movement_speed;
	GLfloat	sensitivity;
	GLfloat	pitch;
	GLfloat	yaw;
	GLfloat	roll;
}				t_camera;

typedef struct	s_window
{
	SDL_Window		*win;
	SDL_GLContext	contex;
	int				width;
	int				height;
	bool			open;
}				t_window;

t_window	init(char *name, int width, int height);
GLuint	get_shader(const char *vertex_name, const char *fragment_name);
void	update_model_matrix(t_mesh *mesh);
t_mesh	get_mesh(const char *name);
void	delete_mesh(t_mesh *mesh);
void	update_mesh_uniform(t_mesh *mesh, GLuint shader);
t_camera	init_cam();
t_mat4	get_view_matrix(t_camera *cam);
//TODO rm
void	display_mat(t_mat4 mat);
//

//MATH
t_vec3f	sub_vec3f(t_vec3f a, t_vec3f b);
t_mat4	identity_matrix(void);
t_mat4	translation_matrix(t_mat4 mat, t_vec3f vec);
t_mat4	rotation_matrix(t_mat4 mat, float angl, t_vec3f vec);
t_mat4	scale_matrix(t_mat4 mat, t_vec3f vec);
t_mat4	perspective_matrix(float fov, float ar, float near, float far);

t_vec3f	mult_matrix_vector(t_vec3f vec, t_mat4 mat);
t_vec3f	normalize_vector(t_vec3f vec);
t_vec3f	cross_vector(t_vec3f a, t_vec3f b);
t_vec3f	add_vector(t_vec3f a, t_vec3f b);
t_vec3f	sub_vector(t_vec3f a, t_vec3f b);
float	dot_vector(t_vec3f a, t_vec3f b);

t_vertex	array[32];

unsigned int	idx[6];

#endif
