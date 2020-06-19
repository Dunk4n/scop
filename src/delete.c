/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 11:48:55 by niduches          #+#    #+#             */
/*   Updated: 2020/06/18 18:41:16 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	unload_gl_mesh(t_mesh *mesh)
{
	glDeleteBuffers(1, &mesh->array_buffer_index);
	glDeleteBuffers(1, &mesh->array_buffer);
	glDeleteVertexArrays(1, &mesh->array_obj);
	mesh->load = false;
}

void	delete_mesh(t_mesh *mesh)
{
	if (mesh->load)
		unload_gl_mesh(mesh);
	free(mesh->vertex);
	mesh->vertex = NULL;
	free(mesh->index);
	mesh->index = NULL;
	mesh->nb_vertex = 0;
	mesh->nb_index = 0;
}

void	delete_obj(t_obj *obj)
{
	uint	i;

	i = 0;
	while (i < obj->nb_mesh)
		delete_mesh(&obj->meshs[i++]);
	free(obj->meshs);
	obj->meshs = NULL;
	obj->nb_mesh = 0;
	obj->load = false;
}

void	delete_material_mega(t_mega_obj *mega)
{
	uint	i;

	i = 0;
	while (i < mega->nb_material)
	{
		if (mega->materials[i].diffuse_tex.data)
		{
			unload_texture(&mega->materials[i].diffuse_tex);
			free(mega->materials[i].diffuse_tex.data);
			mega->materials[i].diffuse_tex.data = NULL;
		}
		if (mega->materials[i].specular_tex.data)
		{
			unload_texture(&mega->materials[i].specular_tex);
			free(mega->materials[i].specular_tex.data);
			mega->materials[i].specular_tex.data = NULL;
		}
		++i;
	}
	free(mega->materials);
	mega->materials = NULL;
	mega->nb_material = 0;
	unload_texture(&mega->tex);
	free(mega->tex.data);
	mega->tex.data = NULL;
}

void	delete_mega(t_mega_obj *mega)
{
	uint	i;

	if (!mega)
		return ;
	i = 0;
	while (i < mega->nb_obj)
		delete_obj(&mega->objs[i++]);
	free(mega->objs);
	mega->objs = NULL;
	mega->nb_obj = 0;
	delete_material_mega(mega);
}
