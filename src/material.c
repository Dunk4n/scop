/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 11:51:47 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 17:02:03 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	init_new_material(t_material *mat)
{
	mat->ambient = (t_vec3f){0, 0, 0};
	mat->diffuse = (t_vec3f){0, 0, 0};
	mat->specular = (t_vec3f){0, 0, 0};
	mat->shininess = 0;
	mat->transparency = 1;
	mat->dencity = 1;
	mat->illum = 2;
	mat->diffuse_tex.data = NULL;
	mat->specular_tex.data = NULL;
}

void	free_materials(t_material *materials, uint nb_material)
{
	uint	i;

	i = 0;
	while (i < nb_material)
	{
		free(materials[i].diffuse_tex.data);
		materials[i].diffuse_tex.data = NULL;
		free(materials[i].specular_tex.data);
		materials[i].specular_tex.data = NULL;
		++i;
	}
}

int		get_material(char *filename, t_mega_obj *mega)
{
	char	path[PATH_MAX + 1];

	if (!filename || !mega)
	{
		free_materials(mega->materials, mega->nb_material);
		return (0);
	}
	ft_strcpy(path, MATERIAL_PATH);
	ft_strcat(path, "/");
	ft_strcat(path, filename);
	if (!load_mtl(path, mega))
	{
		free_materials(mega->materials, mega->nb_material);
		return (0);
	}
	return (1);
}
