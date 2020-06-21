/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_mtl_remove_comment.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 15:35:59 by niduches          #+#    #+#             */
/*   Updated: 2020/06/21 15:37:32 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static void	resize_mtl(char **line, char *tmp, t_mtl_vector *mtl)
{
	uint	nb;

	tmp += pass_spaces(tmp);
	tmp += get_uint(tmp, &nb);
	tmp += pass_spaces(tmp);
	if (*tmp || !nb || nb > 10000)
		return ;
	if (!(mtl->materials = malloc(sizeof(t_material) * nb)))
	{
		free(*line);
		*line = NULL;
		return ;
	}
	mtl->capacity_material = nb;
}

void		remove_mtl_comment(char **line, t_mtl_vector *mtl)
{
	char	*tmp;
	uint	i;

	tmp = *line;
	while (*tmp)
	{
		if (*tmp == '#')
		{
			i = 0;
			while (*line && *(tmp + i) && !mtl->capacity_material)
			{
				if (*(tmp + i) == 'M' &&
				!ft_strncmp(tmp + i, "Material Count:", 15))
					resize_mtl(line, tmp + i + 15, mtl);
				++i;
			}
			if (*line)
				**line = '\0';
			return ;
		}
		++tmp;
	}
}
