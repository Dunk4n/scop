/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 11:21:07 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 15:27:31 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		get_texture(char *name, GLenum type, t_texture *tex)
{
	char	path[PATH_MAX + 1];

	if (!tex)
		return (0);
	ft_strcpy(path, TEXTURE_PATH);
	ft_strcat(path, "/");
	ft_strcat(path, name);
	*tex = get_bmp(path, type);
	if (!tex->data)
		return (0);
	return (1);
}
