/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 14:41:51 by niduches          #+#    #+#             */
/*   Updated: 2020/04/25 01:13:11 by niduches         ###   ########.fr       */
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
# include "../libft/libft.h"

# define NB_KEYWORD 9

typedef unsigned int uint;

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

typedef struct	s_vec3ui
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	z;
}				t_vec3ui;

typedef struct	s_vertex
{
	t_vec3f	position;
	t_vec3f	normal;
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
	unsigned int	material;
	char			name[64];
}				t_mesh;

typedef struct	s_obj
{
	t_mesh			*meshs;
	unsigned int	nb_mesh;
	t_vec3f			position;
	t_vec3f			origin;
	t_vec3f			rotation;
	t_vec3f			scale;
	t_mat4			model_matrix;
	char			name[64];
	bool			load;
}				t_obj;

typedef struct	s_material
{
}				t_material;

typedef struct	s_mega_obj
{
	t_obj			*objs;
	t_material		*materials;
	unsigned int	nb_obj;
	unsigned int	nb_material;
}				t_mega_obj;

typedef struct	s_load_vertex
{
	t_vec3f			*position;
	t_vec3f			*normal;
	t_vec2f			*texture;
	unsigned int	nb_position;
	unsigned int	nb_normal;
	unsigned int	nb_texture;
	unsigned int	capacity_position;
	unsigned int	capacity_normal;
	unsigned int	capacity_texture;
}				t_load_vertex;

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
int		load_obj(t_mega_obj *mega, const char *name);
void	init_obj(t_obj *obj);
void	init_mesh(t_mesh *mesh);
unsigned int	pass_spaces(char *line);
unsigned int	pass_word(char *line);

int		parse_position(char *line, t_load_vertex *array, t_mega_obj *mega);
int		parse_normal(char *line, t_load_vertex *array, t_mega_obj *mega);
int		parse_texture(char *line, t_load_vertex *array, t_mega_obj *mega);
int		parse_face(char *line, t_load_vertex *array, t_mega_obj *mega);
uint	get_int(char *str, int *nb);
uint	get_float(char *line, float *nb);
uint	get_uint(char *str, uint *nb);
t_obj	*get_actual_obj(t_mega_obj *mega);
t_mesh	*get_actual_mesh(t_mega_obj *mega);
int		parse_group(char *line, t_load_vertex *array, t_mega_obj *mega);
int		parse_obj(char *line, t_load_vertex *array, t_mega_obj *mega);
int		parse_s(char *line, t_load_vertex *array, t_mega_obj *mega);
int		format_obj(t_obj *obj, t_load_vertex *array);
int		parse_mtllib(char *line, t_load_vertex *array, t_mega_obj *mega);
int		parse_usemtl(char *line, t_load_vertex *array, t_mega_obj *mega);

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
