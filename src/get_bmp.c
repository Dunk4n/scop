/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 22:09:51 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 01:49:11 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "scop.h"

void	load_texture(t_texture *tex)
{
	if (!tex || !tex->data || tex->load)
		return ;
	glGenTextures(1, &tex->id);
	glBindTexture(tex->type, tex->id);
	glTexParameteri(tex->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(tex->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(tex->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(tex->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(tex->type, 0, GL_RGBA, tex->width, tex->height, 0, GL_RGBA,
GL_UNSIGNED_BYTE, tex->data);
	glGenerateMipmap(tex->type);
	glActiveTexture(0);
	glBindTexture(tex->type, 0);
	tex->load = true;
}

void	unload_texture(t_texture *tex)
{
	if (!tex || !tex->load)
		return ;
	glDeleteTextures(1, &tex->id);
}

void	bind_texture(t_texture *tex, const GLint pos)
{
	glActiveTexture(GL_TEXTURE0 + pos);
	glBindTexture(tex->type, tex->id);
}

void	unbind_texture(t_texture *tex)
{
	glActiveTexture(0);
	glBindTexture(tex->type, 0);
}

static int	bmp_get_header(int fd, t_texture *new, unsigned int *data_size)
{
	char			file_header[14];
	char			info_header[255];
	unsigned char	header_size;
	ssize_t			size;

	new->data = NULL;
	new->load = false;
	if ((size = read(fd, file_header, 14)) != 14)
		return (0);
	header_size = file_header[10];
	if (header_size < 23 || file_header[0] != 'B' || file_header[1] != 'M')
		return (0);
	*data_size = *(unsigned int*)(file_header + 2) - header_size;
	if ((size = read(fd, info_header, header_size - 14)) != header_size - 14)
		return (0);
	new->width = *(unsigned int*)(info_header + 4);
	new->height = *(unsigned int*)(info_header + 8);
	return (1);
}

void	swap_red_blue(unsigned int *color)
{
	unsigned char	tmp;

	tmp = *(unsigned char*)color;
	*(unsigned char*)color = *((unsigned char*)color + 2);
	*((unsigned char*)color + 2) = tmp;
}

static void	bmp_format_data(t_texture *tex)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < tex->height / 2)
	{
		j = 0;
		while (j < tex->width)
		{
			swap_red_blue(((unsigned int*)(tex->data)) + (i * tex->width) + j);
			swap_red_blue(((unsigned int*)(tex->data)) +
((tex->height - 1 - i) * tex->width) + j);
			++j;
		}
		++i;
	}
}

t_texture	get_bmp(char *name, GLenum type)
{
	t_texture		new;
	int				fd;
	ssize_t			size;
	unsigned int	data_size;

	new.type = type;
	if ((fd = open(name, O_RDONLY)) < 0)
		return (new);
	if (!bmp_get_header(fd, &new, &data_size) ||
!(new.data = malloc(sizeof(char) * (data_size))))
	{
		close(fd);
		return (new);
	}
	if ((size = read(fd, new.data, data_size)) != data_size)
	{
		free(new.data);
		new.data = NULL;
		close(fd);
		return (new);
	}
	close(fd);
	bmp_format_data(&new);
	return (new);
}
