/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 11:51:47 by niduches          #+#    #+#             */
/*   Updated: 2020/06/17 15:02:40 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

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
