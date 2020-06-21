/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 10:40:04 by niduches          #+#    #+#             */
/*   Updated: 2020/06/20 21:47:50 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "scop.h"

static GLuint	link_program(GLuint vertex, GLuint geometry, GLuint fragment)
{
	char	info[512];
	GLuint	prog;
	GLint	success;

	prog = glCreateProgram();
	glAttachShader(prog, vertex);
	glAttachShader(prog, geometry);
	glAttachShader(prog, fragment);
	glLinkProgram(prog);
	glGetProgramiv(prog, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(prog, 512, NULL, info);
		ft_printf("\033[0;31mERROR\033[0m::SHADER::COULD_NOT_LINK_PROGRAM\n%s",
		info);
		glUseProgram(0);
		return (0);
	}
	glUseProgram(0);
	return (prog);
}

static char		*add_str(char *src, char buff[4096], ssize_t size)
{
	ssize_t	i;
	ssize_t	j;
	char	*new;
	char	*tmp;

	i = 0;
	while (src && src[i])
		++i;
	if (!(new = malloc(i + size + 1)))
	{
		free(src);
		return (NULL);
	}
	tmp = new;
	i = 0;
	while (src && src[i])
		*(new++) = src[i++];
	free(src);
	j = 0;
	while (buff[j])
		*(new++) = buff[j++];
	*new = '\0';
	return (tmp);
}

static char		*load_shader_source(const char *name)
{
	char	*src;
	ssize_t	size;
	char	buff[4096];
	int		fd;

	if ((fd = open(name, O_RDONLY)) == -1)
		return (NULL);
	src = NULL;
	size = 1;
	while (size > 0)
	{
		if ((size = read(fd, buff, 4095)) <= 0)
			break ;
		buff[size] = '\0';
		if (!(src = add_str(src, buff, size)))
			return (NULL);
	}
	if (size < 0)
	{
		free(src);
		return (NULL);
	}
	return (src);
}

static GLuint	load_shader(GLenum type, const char *name)
{
	char	info[512];
	char	*src;
	GLuint	shader;
	GLint	success;

	if (!(src = load_shader_source(name)))
		return (0);
	if (!(shader = glCreateShader(type)))
	{
		free(src);
		return (0);
	}
	glShaderSource(shader, 1, (const GLchar**)&src, NULL);
	glCompileShader(shader);
	free(src);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, info);
		ft_printf(
		"\033[0;31mERROR\033[0m::SHADER::COULD_NOT_COMPILE_SHADER\n%s", info);
		return (0);
	}
	return (shader);
}

GLuint			get_shader(const char *vertex_name, const char *geometry_name,
const char *fragment_name)
{
	GLuint	vertex_shader;
	GLuint	geometry_shader;
	GLuint	fragment_shader;
	GLuint	program;

	if (!vertex_name || !fragment_name)
		return (0);
	if (!(vertex_shader = load_shader(GL_VERTEX_SHADER, vertex_name)))
		return (0);
	if (!(geometry_shader = load_shader(GL_GEOMETRY_SHADER, geometry_name)))
	{
		glDeleteShader(vertex_shader);
		return (0);
	}
	if (!(fragment_shader = load_shader(GL_FRAGMENT_SHADER, fragment_name)))
	{
		glDeleteShader(vertex_shader);
		glDeleteShader(geometry_shader);
		return (0);
	}
	program = link_program(vertex_shader, geometry_shader, fragment_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(geometry_shader);
	glDeleteShader(fragment_shader);
	return (program);
}
