/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_gl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 16:26:02 by niduches          #+#    #+#             */
/*   Updated: 2020/04/25 18:48:51 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	load_gl_mesh(t_mesh *mesh)
{
	if (mesh->load)
		return ;
	glGenVertexArrays(1, &mesh->array_obj);
	glBindVertexArray(mesh->array_obj);
	glGenBuffers(1, &mesh->array_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->array_buffer);
	glBufferData(GL_ARRAY_BUFFER, mesh->nb_vertex * sizeof(t_vertex),
mesh->vertex, GL_STATIC_DRAW);
	glGenBuffers(1, &mesh->array_buffer_index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->array_buffer_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->nb_index * sizeof(unsigned int),
mesh->index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
(GLvoid*)offsetof(t_vertex, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
(GLvoid*)offsetof(t_vertex, normal));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(t_vertex),
(GLvoid*)offsetof(t_vertex, texcoord));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
	mesh->load = true;
}

void	load_gl_obj(t_obj *obj)
{
	uint	i;

	if (obj->load)
		return ;
	i = 0;
	while (i < obj->nb_mesh)
		load_gl_mesh(&obj->meshs[i++]);
	obj->load = true;
}

void	load_gl_mega(t_mega_obj *mega)
{
	uint	i;

	i = 0;
	while (i < mega->nb_obj)
		load_gl_obj(&mega->objs[i++]);
}
