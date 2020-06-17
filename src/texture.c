/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 11:21:07 by niduches          #+#    #+#             */
/*   Updated: 2020/06/17 12:11:51 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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
