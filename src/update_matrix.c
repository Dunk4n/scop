/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 17:41:34 by niduches          #+#    #+#             */
/*   Updated: 2020/06/09 17:49:51 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	update_matrix(t_mega_obj *mega)
{
	uint	i;
	uint	j;

	i = 0;
	while (i < mega->nb_obj)
	{
		update_obj_matrix(&mega->objs[i]);
		j = 0;
		while (j < mega->objs[i].nb_mesh)
		{
			update_mesh_matrix(&mega->objs[i].meshs[j],
			mega->objs[i].model_matrix);
			++j;
		}
		++i;
	}
}

